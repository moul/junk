pow = Math.pow;

function base(n, to, from) {
    return parseInt(n, from || 10).toString(to);
}

$(document).ready(function() {
                      $('table tbody tr').each(function() {
                                                   //$('.calcul', this).css('background', 'red');
                                               });

                      $('table tbody .calcul').keyup(function() {
                                                         var calcul = $(this).attr('value');
                                                         var jscalcul = mathjs(calcul);
                                                         $('.debug', $(this).parent().parent()).attr('value', jscalcul);
                                                         try {
                                                             var result = eval(jscalcul);
                                                         } catch (x) {
                                                             var result = 'Parse error';
                                                         }
                                                         $('.result', $(this).parent().parent()).attr('value', result);
                                                         air.Introspector.Console.log('test');

                                                        });

                      $('table .calcul:first').focus().keyup();
});