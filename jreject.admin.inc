<?php
/**
 * @file
 * Admin screen forms to configure the jReject module.
 *
 * @author Domenic Santangelo (entendu) http://drupal.org/user/173461
 */

/**
 * jReject main configuration.
 */
function jreject_configure_system() {
  // @todo use i18n_string.
  $form = array();
  $form['jreject_enable'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('jreject_enable', FALSE),
    '#title' => t('Enable jReject'),
  );
  $form['jreject_header'] = array(
    '#type' => 'textfield',
    '#size' => 100,
    '#maxlength' => 256,
    '#default_value' => variable_get('jreject_header', ''),
    '#title' => t('Modal header message'),
  );
  $form['jreject_paragraph1'] = array(
    '#type' => 'textarea',
    '#cols' => 60,
    '#rows' => 5,
    '#default_value' => variable_get('jreject_paragraph1', ''),
    '#title' => t('Modal paragraph 1'),
    '#description' => t('You are encouraged to keep this brief.'),
  );
  $form['jreject_paragraph2'] = array(
    '#type' => 'textarea',
    '#cols' => 60,
    '#rows' => 5,
    '#default_value' => variable_get('jreject_paragraph2', ''),
    '#title' => t('Modal paragraph 2'),
    '#description' => t('You are encouraged to keep this brief.'),
  );
  $form['jreject_close_message'] = array(
    '#type' => 'textfield',
    '#size' => 100,
    '#maxlength' => 256,
    '#default_value' => variable_get('jreject_close_message', ''),
    '#title' => t('Modal close message'),
  );
  $form['jreject_close_link'] = array(
    '#type' => 'textfield',
    '#size' => 50,
    '#maxlength' => 256,
    '#default_value' => variable_get('jreject_close_link', ''),
    '#title' => t('Title of the modal close link'),
  );
  $form['jreject_close_url'] = array(
    '#type' => 'textfield',
    '#size' => 50,
    '#maxlength' => 256,
    '#default_value' => variable_get('jreject_close_url', ''),
    '#title' => t('Modal close URL'),
    '#description' => t('If you want to send your users somewhere special when they click the close link, enter the destination here.'),
  );

  return system_settings_form($form);
}

/**
 * jReject options configuration.
 */
function jreject_configure_options() {
  $form = array();
  $form['jreject_close'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('jreject_close', 1),
    '#title' => t('Allow closing of modal window?'),
  );
  $form['jreject_close_esc'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('jreject_close_esc', 1),
    '#title' => t('Allow closing the modal window with the ESC key?'),
  );
  $form['jreject_close_cookie'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('jreject_close_cookie', 0),
    '#title' => t('Remember if the window was closed by setting a cookie?'),
  );
  $form['jreject_overlay_bg_color'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#maxlength' => 7,
    '#default_value' => variable_get('jreject_overlay_bg_color', '#000'),
    '#title' => t('Overlay background color'),
    '#description' => t('Enter a custom overlay background color in hex.'),
  );
  $form['jreject_overlay_opacity'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#maxlength' => 7,
    '#default_value' => variable_get('jreject_overlay_opacity', '0.8'),
    '#title' => t('Background opacity'),
    '#description' => t('Enter a value from 0-1.'),
  );
  $form['jreject_fade_in_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Modal fade-in speed'),
    '#size' => 10,
    '#maxlength' => 7,
    '#default_value' => variable_get('jreject_fade_in_time', 'fast'),
    '#description' => t("Enter a value ('slow','medium','fast' or integer in ms)"),
  );
  $form['jreject_fade_out_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Modal fade-out speed'),
    '#size' => 10,
    '#maxlength' => 7,
    '#default_value' => variable_get('jreject_fade_out_time', 'fast'),
    '#description' => t("Enter a value ('slow','medium','fast' or integer in ms)"),
  );

  return system_settings_form($form);
}

/**
 * jReject browser rejection configuration.
 */
function jreject_configure_browsers() {
  $form = array();
  $form['intro'] = array(
    '#type' => 'item',
    '#markup' => t('Select the browser types and versions you want to display the modal popup for:'),
  );

  $browsers = jreject_get_reject_browsers();

  $form['jreject_reject_browsers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reject browsers'),
    '#tree' => TRUE,
  );

  foreach (jreject_get_list_browsers() as $key => $options) {
    $form['jreject_reject_browsers'][$key] = array(
      '#type' => 'fieldset',
      '#title' => t('@label settings', array('@label' => $options['label'])),
      '#tree' => TRUE,
    );
    $form['jreject_reject_browsers'][$key]['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Reject browser @label', array('@label' => $options['label'])),
      '#default_value' => isset($browsers[$key]['enabled']) ? $browsers[$key]['enabled'] : 0,
    );
    $form['jreject_reject_browsers'][$key]['reject_version'] = array(
      '#type' => 'textfield',
      '#title' => t('Version of browser'),
      '#default_value' => isset($browsers[$key]['reject_version']) ? $browsers[$key]['reject_version'] : '',
      '#description' => t('If your version of browser is equal or less than specified, it will be  rejected. Leave empty if need to reject all versions.'),
      '#element_validate' => array('element_validate_integer_positive'),
    );
  }

  $form = system_settings_form($form);

  return $form;
}

/**
 * jReject alternatives configuration.
 */
function jreject_configure_alternatives() {
  $conf = variable_get('jreject_browser_alternatives', array());
  $form = array();
  $form['intro'] = array(
    '#type' => 'item',
    '#markup' => '<p>' . t("Select which browsers you'd like to present as upgrades in the modal window.
                      It is recommended that you choose at least three.") . '</p>',
  );
  $form['jreject_msie'] = array(
    '#type' => 'checkbox',
    '#default_value' => $conf['msie'],
    '#title' => 'Internet Explorer',
  );
  $form['jreject_firefox'] = array(
    '#type' => 'checkbox',
    '#default_value' => $conf['firefox'],
    '#title' => 'Firefox',
  );
  $form['jreject_safari'] = array(
    '#type' => 'checkbox',
    '#default_value' => $conf['safari'],
    '#title' => 'Safari',
  );
  $form['jreject_opera'] = array(
    '#type' => 'checkbox',
    '#default_value' => $conf['opera'],
    '#title' => 'Opera',
  );
  $form['jreject_chrome'] = array(
    '#type' => 'checkbox',
    '#default_value' => $conf['chrome'],
    '#title' => 'Chrome',
  );
  $form['submit'] = array(
    "#type" => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for browser alternatives form.
 */
function jreject_configure_alternatives_submit($form, &$form_state) {
  variable_del('jreject_browser_alternatives');
  $config = jreject_prepare_settings($form_state);
  variable_set('jreject_browser_alternatives', $config);
  drupal_set_message(t("Saved options."));
}

/**
 * Utility: prepares form values to be saved.
 */
function jreject_prepare_settings($form_state) {
  $config = array();
  foreach ($form_state['values'] as $k => $item) {
    if (strpos($k, "jreject_") === 0) {
      $config[substr($k, 8, strlen($k))] = $item;
    }
  }
  return $config;
}
