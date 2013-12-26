class Dashing.TrafficLights extends Dashing.Widget
  ready: ->
    @onData(this)
 
  onData: (data) ->
    widget = $(@node)
    widget.find('.light').removeClass('on above')
    widget.find('.light.red').addClass('on') if data.status == 'red'
    widget.find('.light.amber').addClass('on') if data.status == 'amber'
    widget.find('.light.green').addClass('on') if data.status == 'green'
    widget.find('.light.amber').addClass('above') if data.status == 'red'
    widget.find('.light.green').addClass('above') if data.status == 'red' || data.status == 'amber'
