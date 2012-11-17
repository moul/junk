print __file__

class jambeDbAction:
    def __init__(self, table_name, Db):
        self._table_name = table_name
        self._db = Db
        self._jambe = Db._jambe

        self._values = []
        self._fields = []
        self._where = []
        self._group = []
        self._order = []

    def values(self, values):
        self._values.append(values)
        return self

    def fields(self, fields):
        self._fields = fields
        return self

    def where(self, where):
        if where:
            self._where.append(where)
        return self

    def _execute_query(self, query):
        return self._db.query(query)

    def _prepare_query(self):
        raise notImplementedError

    def execute(self):
        query = self._prepare_query()
        return self._execute_query(query)

class jambeDbInsert(jambeDbAction):
    pass

class jambeDbSelect(jambeDbAction):
    pass

class jambeDbUpdate(jambeDbAction):
    pass

class jambeDbResource():
    def __init__(self, db):
        self._db = db

    def fetch_one(self):
        raise notImplementedError

    def fetch_all(self):
        raise notImplementedError

class jambeDb():
    _insert = jambeDbInsert
    _select = jambeDbSelect
    _update = jambeDbUpdate

    def __init__(self, jambe):
        self._jambe = jambe

    def create_table(self, table_name, schema):
        raise self._jambe.Exception("jambeDB::create_table")

    def install_from_schemas(self, schemas):
        for table_name in schemas:
            self.create_table(table_name, schemas[table_name])

    def uninstall_from_schemas(self, schemas):
        for table_name in schemas:
            self.drop_table(table_name)

    def update(self, table_name):
        return self._update(table_name, self)

    def insert(self, table_name):
        return self._insert(table_name, self)

    def select(self, table_name):
        return self._select(table_name, self)

    def query(self, query, args = {}):
        raise notImplementedError
