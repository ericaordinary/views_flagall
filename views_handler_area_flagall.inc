<?php
class views_handler_area_flagall extends views_handler_area {

  /**
   * Implements views_object#option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['title'] = array('default' => 'Flag all', 'translatable' => TRUE);
		$options['flags'] = array('default' => '');
    return $options;
  }

  /**
   * Implements views_handler#option_form().
   */
	function options_form(&$form, &$form_state) {
		parent::options_form($form, $form_state);
		$flags = flag_get_flags();
		$form['title'] = array(
			'#type' => 'textfield',
			'#title' => t('Link title'),
			'#description' => t('Set the title for the flag all link.'),
			'#default_value' => $this->options['title'],
		);

		$form['flags'] = array(
		  '#type' => 'checkboxes',
			'#title' => t('Flags'),
			'#description' => t('Select which flags to apply'),
			'#options' => views_handler_area_flagall_get_flag_list($flags),
			'#required' => TRUE,
      '#default_value' => $this->options['flags'],
		);
	}

	function options_submit(&$form, &$form_state) {
		parent::options_submit($form, $form_state);
	}

	/**
   * Implements views_handler_area#render().
   */
	function render($empty = FALSE) {
    if ((!$empty || !empty($this->options['empty'])) && !empty($this->options['flags'])) {
      // Return the flags that should be applied.
			$flags = implode(',', $this->options['flags']);

      // Return the nids of the view results.
      $nids_array = array();
      foreach ($this->view->result as $result) {
        $nids_array[] = $result->nid;
      }
      $nids = implode(',', $nids_array);

      // Get the current path so we can return the user back here once the flagging is done.
      $destination = drupal_get_destination();

      // Set a default title if no title is set by the user.
      $link_title = $this->options['title'] ? $this->options['title'] : 'Flag all';

      // Return a Flag All link with the flags, nids and destination as an argument.
      return l(
			  $link_title,
        'flagall',
				array(
					'query' => 'flags=' . $flags . '&nids=' . $nids . '&' . $destination,
				  'attributes' => array(
  				  'class' => 'flag-all',
			 	  ),
				)
			);
		}
		return '';
	}
}

function views_handler_area_flagall_get_flag_list($flags) {
	// Return an array of available flags.
	$flag_list = array();
	foreach($flags as $flag) {
		$flag_list[$flag->name] = $flag->title;
	}
	return $flag_list;
}


