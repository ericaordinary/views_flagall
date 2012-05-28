<?php

/**
 * Implements hook_views_data().
 */
function views_flagall_views_data() {
	$data['views']['flagall'] = array(
    'title' => t('Flag all'),
		'help' => t('Add a link to flag all items in the view result.'),
		'area' => array(
			'handler' => 'views_handler_area_flagall'
		),
  );
	return $data;
}


/**
 * Implements hook_views_handlers().
 */
function views_flagall_views_handlers() {
  $handlers = array(
    'info' => array(
      'path' => drupal_get_path('module', 'views_flagall'),
    ),
    'handlers' => array(
      'views_handler_area_flagall' => array(
        'parent' => 'views_handler_area',
      ),
    ),
  );
  return $handlers;
}
