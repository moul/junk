print __file__

import jambe.libs.db

class jambeSqlite3Insert(jambe.libs.db.jambeDbInsert):
    def _prepare_query(self):
        fields = ', '.join(self._fields)
        placeholders = ', '.join(['?' for i in self._fields])
        return "insert into %s(%s) values (%s)" % (self._table_name, fields, placeholders)

    def _execute_query(self, query):
        queries = []
        for values in self._values:
            queries.append(self._db.query(query, values))
        return queries

class jambeSqlite3Select(jambe.libs.db.jambeDbSelect):
    def _prepare_query(self):
        _from = 'from %s' % self._table_name

        if len(self._fields):
            _fields = ', '.join(self._fields)
        else:
            _fields = '*'

        if len(self._where):
            _where = 'where %s' % ' and '.join(self._where)
        else:
            _where = ''

        if len(self._order):
            _order = 'order by %s' % ', '.join(self._order)
        else:
            _order = ''

        if len(self._group):
            _group = 'group by %s' % ', '.join(self._group)
        else:
            _group = ''

        query = 'select %s %s %s %s %s' % (_fields, _from, _where, _order, _group)
        return query

class jambeSqlite3Update(jambe.libs.db.jambeDbUpdate):
    def _prepare_query(self):
        return 'select 2,3,4'

class jambeSqlite3Resource(jambe.libs.db.jambeDbResource):
    _query = ''
    _args = {}

    def __init__(self, _db):
        jambe.libs.db.jambeDbResource.__init__(self, _db)
        self._cu = self._db.conn.cursor()

    def set_query(self, query, args = {}):
        self._query = query
        self._args = args

    def execute(self):
        if self._args:
            self._res = self._cu.execute(self._query, self._args)
        else:
            self._res = self._cu.execute(self._query)
        return self

    def fetch_one(self):
        return self._res.fetchone()

    def fetch_all(self):
        return self._res.fetchall()

class jambeSqlite3(jambe.libs.db.jambeDb):
    _types_translation = {'int': 'integer'}
    _insert = jambeSqlite3Insert
    _select = jambeSqlite3Select
    _resource = jambeSqlite3Resource

    def reconnect(self):
        import sqlite3
        conn = sqlite3.connect(self._netloc)
        self.conn = conn

    def connect(self, scheme = 'sqlite3', netloc = None, path = None, params = None, query = None, fragment = None):
        self._netloc = netloc
        return self.reconnect()

    def table_exists(self, table_name):
        import sqlite3
        try:
            self.query('select 1 from %s' % table_name)
            return True
        except sqlite3.OperationalError, e:
            return False

    def drop_table(self, table_name):
        self.query('drop table %s' % table_name)

    def create_table(self, table_name, schema):
        import sqlite3
        elements = []
        for field_name in schema['fields']:
            field = schema['fields'][field_name]
            not_null = field['not null'] == True and 'not null' or ''
            default = ''
            type = field['type']
            if type in self._types_translation:
                type = self._types_translation[type]
            if 'default' in field:
                if type in ['varchar', 'text']:
                    field['default'] = "'%s'" % field['default']
                default = 'default (%s)' % field['default']
            if type == 'serial':
                not_null = ''
            size = 'length' in field and '(%s)' % field['length'] or ''
            elements.append("%s %s %s %s %s" % (field_name, type, size, not_null, default))
        elements.append('primary key (%s)' % ','.join(schema['primary key']))
        if 'unique key' in schema:
            elements.append('unique key (%s)' % ','.join(schema['unique key']))
#        if 'indexes' in schema:
#            for index_name in schema['indexes']:
#                index = schema['indexes'][index_name]
#                elements.append('index (%s)' % ','.join(index))
        query = 'create table %s (%s)' % (table_name, ', '.join(elements))
        try:
            self.query(query)
        except sqlite3.OperationalError, e:
            raise self._jambe.Exception("create_table: %s (%s)" % (table_name, e))

    def query(self, query, args = {}):
        self._jambe.Log.log('Query: "%s", args: "%s"' % (query, args))
        resource = self._resource(self)
        resource.set_query(query, args = args)
        resource.execute()
        return resource

def setup(jambe):
    return jambeSqlite3(jambe)
