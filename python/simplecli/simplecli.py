#!/usr/bin/env python

import CliBase

class CliPoney(CliBase.CliBase):
    def cmd_toto(self, *args):
        print 'toto', args

    def cmd_titi(self, *args):
        print 'titi'

    def cmd_tata(self, arg1 = 43, arg2 = 42, *args):
        print 'tata', arg1, arg2

if __name__ == "__main__":
    cli = CliPoney()
    cli.run()
