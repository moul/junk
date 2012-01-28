import serial, glob, atexit, sys

__version__ = "0.2"

class Mouluino():
    def __init__(self, port = 'auto', baud = 115200, debug = False, timeout = 2, writeTimeout = 2):
        self.comm = None
        self.debug = debug
        if port == 'auto':
            port = None
            for dev in glob.glob('/dev/tty.usbmodem*'):
                port = dev
        if port:
            try:
                self.comm = serial.Serial(port, baud, timeout = timeout, writeTimeout = writeTimeout)
                if self.debug:
                    print "Serial connection established at port %s" % port
            except:
                print "Could not connect to Arduino at specified port (%s)." % port
                sys.exit(1)
        else:
            print "No port specified"
        atexit.register(self.disconnect)

    def write(self, data):
        self.comm.write(data)

    def read(self, bytes):
        while True:
            if self.comm.inWaiting() > bytes - 1:
                return self.comm.read(bytes)

    def readline(self):
        return self.comm.readline()

    def flushInput(self):
        self.comm.flushInput()

    def disconnect(self):
        if self.comm:
            self.comm.close()
        if self.debug:
            print "Serial connection closed."

class MouluinoSMS(Mouluino):
    def __init__(self, safe_init = False):
        Mouluino.__init__(self)
        if safe_init:
            self.safe_init()
        if self.debug:
            print "MoulinoSMS has been started."

    def safe_init(self):
        self.read_analogs() # hack: init

    def read_analogs(self):
        self.write("r a\r")
        result = self.readline().split()
        return result

    def read_digitals(self):
        self.write("r d\r")
        result = self.readline().split()
        return result

    def read_digital(self, pin):
        if pin in range(2, 14):
            result = self.read_digitals()[1:][pin - 2]
            if self.debug:
                print "Read digital pin %s, value was %s" % (str(pin), result)
            if result == "":
                return None
            return int(result)
        return None

    def read_analog(self, pin):
        if pin in range(6):
            result = self.read_analogs()[1:][pin]
            if self.debug:
                print "Read analog pin %s, value was %s" % (str(pin), result)
            if result == "":
                return None
            return int(result)
        return None

    def write_digital(self, pin, val):
        if pin in range(2, 14) and val in [0, 1]:
            self.write("w d %s %s\r" % (pin, str(val)))
            if self.debug:
                print "Wrote value %s to digital pin %s" % (str(val), pin)

    def write_analog(self, pin, val):
        if pin in [3, 5, 6, 9, 10, 11] and val in range(256):
            self.write("w a %s %s\r" % (pin, str(val)))
            if self.debug:
                print "Wrote value %s to pwm pin %s" % (str(val), pin)
