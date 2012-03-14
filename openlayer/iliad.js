var map;

function init() {
    map = new OpenLayers.Map({
                                 div: "map",
                                 allOverlays: false
                             });
    map.addControl(new OpenLayers.Control.LayerSwitcher());
    map.addControl(new OpenLayers.Control.Navigation({dragPanOptions: {enableKinetic: true}}));
    map.addControl(new OpenLayers.Control.KeyboardDefaults({observeElement: 'map'}));

    var gsat = new OpenLayers.Layer.Google(
        "Google Satellite",
        {type: google.maps.MapTypeId.SATELLITE, numZoomLevels: 22, visibility: true}
    );
    var gphy = new OpenLayers.Layer.Google(
        "Google Physical",
        {type: google.maps.MapTypeId.TERRAIN, visibility: false}
    );
    var gmap = new OpenLayers.Layer.Google(
        "Google Streets", // the default
        {numZoomLevels: 20, visibility: true}
    );
    var ghyb = new OpenLayers.Layer.Google(
        "Google Hybrid",
        {type: google.maps.MapTypeId.HYBRID, numZoomLevels: 22, visibility: true}
    );

    /*var wms = new OpenLayers.Layer.WMS("OpenLayers WMS",
                                       "http://vmap0.tiles.osgeo.org/wms/vmap0", {layers: 'basic'});*/

    var osm = new OpenLayers.Layer.OSM();

    /*
    var binApiKey = "";

    var veroad = new OpenLayers.Layer.Bing({
        key: bingApiKey,
        type: "Road",
        wrapDateLine: true
    });
    var veaer = new OpenLayers.Layer.Bing({
        key: bingApiKey,
        type: "Aerial",
        wrapDateLine: true
    });
    var vehyb = new OpenLayers.Layer.Bing({
        key: bingApiKey,
        type: "AerialWithLabels",
        wrapDateLine: true
    });*/


    var layers = [gmap, gsat, gphy, ghyb/*, wms*/, osm/*, veroad, veaer, vehyb*/];
    for (var i = 1; i < layers.length; i++) {
        console.info("test", layers[i]);
    }
    map.addLayers(layers);

    map.setCenter(new OpenLayers.LonLat(2.38472, 48.840995).transform(
                      new OpenLayers.Projection("EPSG:4326"),
                      map.getProjectionObject()
    ), 12);

    var markers = new OpenLayers.Layer.Markers( "Markers" );
    map.addLayer(markers);

    var size = new OpenLayers.Size(21,25);
    var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
    var icon = new OpenLayers.Icon('http://www.openlayers.org/dev/img/marker.png',size,offset);
    var datacenters = [
        {
            title: "DC1",
            lon: 2.39472,
            lat: 48.890995,
            description: "BLAH"
        }, {
            title: "DC2",
            lon: 2.34472,
            lat: 48.840995,
            description: "BLAH"
        }, {
            title: "DC3",
            lon: 2.34472,
            lat: 48.890995,
            description: "BLAH"
        }, {
            title: "DC4",
            lon: 2.39472,
            lat: 48.840995,
            description: "BLAH"
        }
    ];

    for (var i = 0; i < datacenters.length; i++) {
        var dc = datacenters[i];
        var marker = new OpenLayers.Marker(new OpenLayers.LonLat(dc.lon, dc.lat).transform(
                                               new OpenLayers.Projection("EPSG:4326"),
                                               map.getProjectionObject()) ,icon.clone());
        marker.events.register('mousedown', marker, function(e) {
                                   console.info("test", e);
                                   OpenLayers.Event.stop(e);
                               });
        markers.addMarker(marker);
    }
}
