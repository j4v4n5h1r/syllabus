<?php

// hop new objective

function add_objective() {
	$departments = db_query("SELECT * FROM {syllabus_main_department}");

	$options = array();
	$options2 = array("English", "Polish");

	foreach ($departments as $department) {
		$options[$department -> id] = $department -> department_name;
	}

	$form['name'] = array(
		'#type' => 'textfield',
		'#title' => t("Objective Name:"),
		'#required' => TRUE
		);
	$form['dep'] = array(
		'#type' => 'select',
		'#title' => t('Department:'),
		'#options' => $options,
		'#description' => t('Select <em>Department</em> for the new <em>Objective</em>'),
		'#required' => TRUE
		);
	$form['lang'] = array(
		'#type' => 'select',
		'#title' => t('Language:'),
		'#options' => $options2,
		'#description' => t('Select <em>Language</em> for the new <em>Objective</em>'),
		'#required' => TRUE
		);

	$form["submit"] = array(
		'#type' => 'submit',
		'#value' => 'Add Objective');

	return $form;
}

function add_objective_submit($form, $form_state){
	$id = db_insert('syllabus_main_objective') -> fields(array(
		'name' => $form_state['values']['name'],
		'dep' => $form_state['values']['dep'],
		'lang' => $form_state['values']['lang'],
		)) -> execute();

	drupal_set_message('New Objective has been added!');
}

