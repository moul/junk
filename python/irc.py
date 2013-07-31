#!/usr/bin/env python

from twisted.words.protocols import irc
from twisted.internet import reactor, protocol

import time, sys

class TestBot(irc.IRCClient):
    nickname = 'bobby42head'

    def signedOn(self):
        self.join(self.factory.channel, self.factory.password)

    def joined(self, channel):
        print "joined %s" % channel

    def privmsg(self, user, channel, msg):
        user = user.split('!', 1)[0]
        print '<%s> %s' % (user, msg)

        # private message
        if channel == self.nickname:
            self.msg(user, "yo, i'm a bot")

        # direct message
        if msg.startswith(self.nickname + ':'):
            self.msg(channel, "hey, i'm a bot")



    def action(self, user, channel, msg):
        user = user.split('!')[0]
        print "* %s %s" % (user, msg)

    def irc_NICK(self, prefix, params):
        old_nick = prefix.split('!')[0]
        new_nick - params[0]
        print "old_nick: %s, new_nick: %s" % (old_nick, new_nick)

    def alterCollidedNick(self, nickname):
        return nickname + '_'

class TestBotFactory(protocol.ClientFactory):
    def __init__(self, channel, password):
        self.channel = channel
        self.password = password

    def buildProtocol(self, addr):
        print "buildProtocol"
        p = TestBot()
        p.factory = self
        return p

    def clientConnectionLost(self, connector, reason):
        print "connection lost:", reason
        connection.connect()

    def clientConnectionFailed(self, connector, reason):
        print "connection failed:", reason
        reactor.stop()

if __name__ == '__main__':
    channel = sys.argv[1]
    password = sys.argv[2]
    factory = TestBotFactory(channel, password)
    reactor.connectTCP("irc.freenode.net", 6667, factory)
    reactor.run()
