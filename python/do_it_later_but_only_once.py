#!/usr/bin/env python

MOUL_HACK_ID = 'totopute'
MOUL_HACK_PID = '/tmp/%s.pid' % MOUL_HACK_ID

import os, sys, time

if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == '-moulhack':
        time.sleep(1)
        if os.path.exists(MOUL_HACK_PID):
            print "ZUPER"
            os.unlink(MOUL_HACK_PID)
    else:
        print "CALL"
        open(MOUL_HACK_PID, 'w').close()
        os.spawnlp(os.P_NOWAIT, 'python', 'python', __file__, '-moulhack');
