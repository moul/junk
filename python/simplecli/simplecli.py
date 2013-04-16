#!/usr/bin/env python

import readline
import CliBase

class CliPoney(CliBase.CliBase):
    def cmd_toto(self):
        print 'toto'

    def cmd_titi(self):
        print 'titi'

    def cmd_tata(self, arg1, arg2 = 42):
        print 'tata', arg1, arg2

if __name__ == "__main__":
    cli = CliPoney()
    cli.run()
