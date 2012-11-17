print __file__

import jambe.libs.modules

class Core(jambe.libs.modules.jambeModule):
    _weight = 1000

    def hook_cron(self):
        print "CRONNNNN"
        raise notImplementedError

    def hook_theme_init(self):
        self._jambe.Theme.templates_directory_add('modules/core/templates')

    def hook_install_schemas(self):
        schemas = {}
        schemas['system'] = {'name': 'system',
                             'fields':
                                 {'name':
                                      {'type': 'varchar',
                                       'length': 255,
                                       'not null': True,
                                       'default': ''},
                                  'status':
                                      {'type': 'int',
                                       'not null': True,
                                       'default': 0,
                                       'size': 'tiny'},
                                  'weight':
                                      {'type': 'int',
                                       'not null': True,
                                       'default': 0}},
                             'primary key': ['name'],
                             'indexes': {}}
        return schemas

    def hook_install(self):
        jambe.libs.modules.jambeModule.hook_install(self)

        modules = self._jambe.Mh.list_modules()
        insert = self._jambe.Db.insert('system').fields(['name', 'status', 'weight'])
        for name in modules:
            module = modules[name]
            insert.values([module['name'], module['status'], module['weight']])
        insert.execute()

def setup(jambe):
    return Core(jambe)
