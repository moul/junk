<?php

  /**
   * sec		1 second
   * min		60 seconds
   * hour		3 600 seconds
   * day		86 400 seconds
   * week		604 800 seconds
   * month		2 629 743.83 seconds
   * year		31 556 926 seconds
   **/
function domain_by_date($time, $name) {
  $min_year = 41; // 2011 - 1970 = 41
  $min_month = 5; // may
  $max_year = 42;

  $time = intval($time);
  $human = date('d-m-Y', $time);
  $year = intval($time / 31556926);
  $month = intval($time % 31556926 / 2629743.83);

  $year_words = array('ig2l', 'tz3n', '865v', 'q79m', 'j0br', 'cueh', 'y4df', 'oxaw', 'kp1s');
  $month_words = array('hby', 'jiz', '1vc', 'own', 'x53', 'q0r', 'edu', '2t8', '7mf', '9la', 's6k', '4pg');
  $domain = '';
  if ($year < $min_year || ($year == $min_year && $month < $min_month)) {
    $domain .= 'owoza8';
  } else if ($year > $max_year) {
    $domain .= '61hf9f';
  } else {
    $domain .= $month_words[$month];
    $domain .= $year_words[$year - $min_year];
  }

  $domain .= '.com';
  unset($year_words);//, $month_words);
  print '<tr><td>'.implode('</td><td>', get_defined_vars()).'</td></tr>';
  return $domain;
}

$dates = array();
for ($i = 4; $i > 0; $i--) {
  $dates[$i.' year ago'] = time() - ($i * 31556926);
}
for ($i = 11; $i > 0; $i -= 3) {
  $dates[$i.' month ago'] = time() - ($i * 2629743.83);
}
$dates['previous week'] = time() - 604800;
$dates['yesterday'] = time() - 86400;
$dates['<b>today</b>'] = time();
$dates['tomorrow'] = time() + 86400;
$dates['next week'] = time() + 604800;
for ($i = 1; $i < 24; $i++) {
  $dates[$i.' month later'] = time() + ($i * 2629743.83);
}
for ($i = 2; $i < 7; $i++) {
  $dates[$i.' year later'] = time() + ($i * 31556926);
}


echo '<html><head><style>table{border: 1px solid black;}td{padding:0 8px;}</style></head><body><table>';
$vars = array('time', 'name', 'human', 'domain', 'year', 'month');
print '<tr><td>'.implode('</td><td>', $vars).'</td></tr>';
foreach ($dates as $name => $date) {
  domain_by_date($date, $name);
}
echo '</table></body></html>';
