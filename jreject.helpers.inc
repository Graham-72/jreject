<?php
/**
 * @file
 * Helper functions.
 */

/**
 * Returns list of the variables for module jReject.
 */
function jreject_default_variables() {
  $variables = array(
    'jreject_enable' => 1,
    'jreject_header' => 'Did you know that your Internet Browser is out of date?',
    'jreject_paragraph1' => 'Your browser is out of date, and may not be compatible with our website. A list of the most popular web browsers can be found below.',
    'jreject_paragraph2' => 'Just click on the icons to get to the download page:',
    'jreject_close_message' => 'By closing this window you acknowledge that your experience on this website may be degraded.',
    'jreject_close_link' => 'Close This Window',
    'jreject_close_url' => '#',
    'jreject_close' => 1,
    'jreject_close_esc' => 1,
    'jreject_close_cookie' => 0,
    'jreject_overlay_bg_color' => '#000',
    'jreject_overlay_opacity' => '0.8',
    'jreject_fade_in_time' => 'fast',
    'jreject_fade_out_time' => 'fast',
  );

  return $variables;
}
