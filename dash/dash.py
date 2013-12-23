#!/usr/bin/env python

import os
import logging
from flask import Flask, render_template, Response, send_from_directory, request, current_app

# FIXME: remove
from samplers import get_samplers


PYDASHIE_DIR = 'pydashie/pydashie'


def prefix_path(path):
    return PYDASHIE_DIR + '/' + path


app = Flask(__name__, template_folder=prefix_path('templates'))
logging.basicConfig()
log = logging.getLogger(__name__)


@app.route("/")
def main():
    return render_template('main.html', title='pyDashie')


@app.route("/dashboard/<dashlayout>/")
def custom_layout(dashlayout):
    return render_template('%s.html'%dashlayout, title='pyDashie')


@app.route("/assets/application.js")
def javascripts():
    if not hasattr(current_app, 'javascripts'):
        import coffeescript
        scripts = [
            prefix_path('assets/javascripts/jquery.js'),
            prefix_path('assets/javascripts/es5-shim.js'),
            prefix_path('assets/javascripts/d3.v2.min.js'),

            prefix_path('assets/javascripts/batman.js'),
            prefix_path('assets/javascripts/batman.jquery.js'),

            prefix_path('assets/javascripts/jquery.gridster.js'),
            prefix_path('assets/javascripts/jquery.leanModal.min.js'),

            #prefix_path('assets/javascripts/dashing.coffee'),
            prefix_path('assets/javascripts/dashing.gridster.coffee'),

            prefix_path('assets/javascripts/jquery.knob.js'),
            prefix_path('assets/javascripts/rickshaw.min.js'),

            #prefix_path('assets/javascripts/application.coffee'),
            #prefix_path('assets/javascripts/app.js'),
            'assets/app.js',
            #prefix_path('widgets/clock/clock.coffee'),

            prefix_path('widgets/number/number.coffee'),
        ]

        nizzle = True
        if not nizzle:
            scripts = [prefix_path('assets/javascripts/application.js')]

        output = []
        for path in scripts:
            output.append('// JS: %s\n' % path)
            if '.coffee' in path:
                log.info('Compiling Coffee for %s ' % path)
                contents = coffeescript.compile_file(path)
            else:
                f = open(path)
                contents = f.read()
                f.close()

            output.append(contents)

        if nizzle:
            f = open('/tmp/foo.js', 'w')
            for o in output:
                print >> f, o
            f.close()

            f = open('/tmp/foo.js', 'rb')
            output = f.read()
            f.close()
            current_app.javascripts = output
        else:
            current_app.javascripts = ''.join(output)


    return Response(current_app.javascripts, mimetype='application/javascript')


@app.route('/assets/application.css')
def application_css():
    scripts = [
        prefix_path('assets/stylesheets/application.css'),
    ]
    output = ''
    for path in scripts:
        output = output + open(path).read()
    return Response(output, mimetype='text/css')


@app.route('/assets/images/<path:filename>')
def send_static_img(filename):
    directory = os.path.join(prefix_path('assets'), 'images')
    return send_from_directory(directory, filename)


@app.route('/views/<widget_name>.html')
def widget_html(widget_name):
    html = '%s.html' % widget_name
    path = os.path.join(prefix_path('widgets'), widget_name, html)
    if os.path.isfile(path):
        f = open(path)
        contents = f.read()
        f.close()
        return contents


import Queue


class Z:
    pass
xyzzy = Z()
xyzzy.events_queue = {}
xyzzy.last_events = {}
xyzzy.using_events = True
xyzzy.MAX_QUEUE_LENGTH = 20
xyzzy.stopped = False


@app.route('/events')
def events():
    if xyzzy.using_events:
        event_stream_port = request.environ['REMOTE_PORT']
        current_event_queue = Queue.Queue()
        xyzzy.events_queue[event_stream_port] = current_event_queue
        current_app.logger.info('New Client %s connected. Total Clients: %s' %
                                (event_stream_port, len(xyzzy.events_queue)))

        #Start the newly connected client off by pushing the current last events
        for event in xyzzy.last_events.values():
            current_event_queue.put(event)
        return Response(pop_queue(current_event_queue), mimetype='text/event-stream')

    return Response(xyzzy.last_events.values(), mimetype='text/event-stream')


def pop_queue(current_event_queue):
    while not xyzzy.stopped:
        try:
            data = current_event_queue.get(timeout=0.1)
            yield data
        except Queue.Empty:
            #this makes the server quit nicely - previously the queue threads would block and never exit. This makes it keep checking for dead application
            pass


def purge_streams():
    big_queues = [port for port, queue in xyzzy.events_queue if len(queue) > xyzzy.MAX_QUEUE_LENGTH]
    for big_queue in big_queues:
        current_app.logger.info('Client %s is stale. Disconnecting. Total Clients: %s' %
                                (big_queue, len(xyzzy.events_queue)))
        del queue[big_queue]


def close_stream(*args, **kwargs):
    event_stream_port = args[2][1]
    del xyzzy.events_queue[event_stream_port]
    log.info('Client %s disconnected. Total Clients: %s' % (event_stream_port, len(xyzzy.events_queue)))


def run(app, xyzzy):
    samplers = get_samplers(xyzzy)

    try:
        app.run(debug=True,
                port=5000,
                threaded=True,
                use_reloader=True,
                use_debugger=True
                )
    finally:
        print "Disconnecting clients"
        xyzzy.stopped = True

        print "Stopping %d timers" % len(samplers)
        for (i, sampler) in enumerate(samplers):
            sampler.stop()

    print "Done"


def run_app():
    import SocketServer
    SocketServer.BaseServer.handle_error = close_stream
    run(app, xyzzy)


if __name__ == "__main__":
    run_app()
