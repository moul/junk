rot = 1;

c = ['4390c1', 'eb036d', 'f7f910', '468fc1', 'f50000', '8d107a', '5fab21', 'f68ec3', '4390c1', 'f4000b', '237b26', 'f75600', 'f7f910'];
           
$(document).ready(function() {

  todo = Math.round((((Date.now()/1000)-1351882800)/10800)+1); 
  
  for (i=1; i <= todo; i++) {
    $('#vikanim').append('<div class="bar" style="z-index:'+(14-i)+'; background-color:#'+c[i-1]+'" id="bar_'+i+'"></div>');
  }
  
  $.each($('#vikanim .bar'), function() {
    //$('#'+this.id).animate({'rotate': rot+'deg'}, 3000);
    
    $('#'+this.id).animate({borderSpacing: rot}, {
    step: function(now,fx) {
      $(this).css('-webkit-transform','rotate('+now+'deg)');
      $(this).css('-moz-transform','rotate('+now+'deg)'); 
      $(this).css('-ms-transform','rotate('+now+'deg)'); 
      $(this).css('-o-transform','rotate('+now+'deg)'); 
      $(this).css('transform','rotate('+now+'deg)');  
    },
    duration: 3000
    },'linear');
    
    rot = rot + 6.825;   
  });  
});