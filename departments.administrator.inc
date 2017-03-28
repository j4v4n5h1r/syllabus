<?php

// admin departments

function departments_page() {
	$results = db_query("SELECT * FROM {syllabus_main_department}");

	$header = array(
		'department_name' => 'Department Name', 
		'department_code' => 'Department Code', 
		'hod' => 'Head of Department', 
		// 'button' => 'Open'
		);
	$rows = array();

	foreach ($results as $result) {
		$teachers = db_query("SELECT * FROM {users} WHERE {uid}='" . $result -> hod . "' LIMIT 1") -> fetchObject();
		$teacher = $teachers -> name . " / " . $teachers -> mail;

		$rows[$result -> id] = array(
			'id' => $result -> id,
			'department_name' => $result -> department_name,
			'department_code' => $result -> department_code,
			'hod' => $teacher,
			// 'button' => '<a href="' . base_path() . 'syllabus_main/department_open?idx=' . $result -> id . '">Open</a>'
			);
	}

	$options = array();
	foreach ($rows as $row) {
		$options[$row['id']] = array(
			'department_name' => $row['department_name'],
			'department_code' => $row['department_code'],
			'hod' => $row['hod'],
			// 'button' => $row['button']
			);
	}
	$form['table'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#empty' => t('No departments found'),
		);

	$form['submit_update'] = array(
		'#type' => 'submit',
		'#value' => t('Update'),
		'#submit' => array('departments_page_submit_update'),
		);
	$form['submit_delete'] = array(
		'#type' => 'submit',
		'#value' => t('Delete'),
		'#submit' => array('departments_page_submit_delete'),
		);

	return $form;
}

function departments_page_submit_update($form, $form_state){
	$x = 0;
	$y = 0;
	foreach ($form_state['values']['table'] as $value) {
		if ($value != 0) {
			$y = $value;
			$x++;
		}
	}
	if ($x == 1) {
		drupal_goto('syllabus_main/department_update', array('query' => array('idx' => $y)));
	} else if ($x > 1) {
		drupal_set_message("Please select just one!");
	} else if ($x < 1) {
		drupal_set_message("Please select one!");
	}
}

function departments_page_submit_delete($form, $form_state){
	$x = 0;
	foreach (($form_state['values']['table']) as $lines => $line) {
		if($line) {
			$x++;
			$delete = db_delete('syllabus_main_department')
			->condition('id', $line)
			-> execute();
		}
	}
	if ($x == 0) {
		drupal_set_message('No line selected!');
	}
}

function department_update() {
	$idx = filter_input(INPUT_GET, 'idx');
	$results = db_query("SELECT * FROM {syllabus_main_department} WHERE {id}=" . $idx . " LIMIT 1") -> fetchObject();
	$users = db_query("SELECT * FROM {users}");

	$options = array();

	foreach ($users as $user) {
		$options[$user -> uid] = $user -> name;
	}

	$form['department_name'] = array(
		'#type' => 'textfield',
		'#title' => t("Department Name:"),
		'#default_value' => $results -> department_name,
		'#required' => TRUE
		);
	$form['department_code'] = array(
		'#type' => 'textfield',
		'#title' => t("Department Code:"),
		'#default_value' => $results -> department_code,
		'#required' => TRUE
		);
	$form['hod'] = array(
		'#type' => 'select',
		'#title' => t('Head of Department:'),
		'#options' => $options,
		'#description' => t('Select <em>Head of Department</em> for the new <em>Department</em>'),
		'#default_value' => $results -> hod,
		'#required' => TRUE
		);

	$form['submit_save'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
		'#submit' => array('department_update_submit_save'),
		);
	$form['submit_cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
		'#submit' => array('department_update_submit_cancel'),
		);

	return $form;
}

function department_update_submit_save($form, $form_state){
	$idx = filter_input(INPUT_GET, 'idx');
	if (db_query("UPDATE {syllabus_main_department} SET {department_name}='" . $form_state['values']['department_name'] . "', {department_code}='" . $form_state['values']['department_code'] . "', {hod}=" . $form_state['values']['hod'] . " WHERE {id}=" . $idx)) {
		drupal_goto('syllabus_main/departments');
	} else {
		drupal_set_message('Some Problem!');
	}
}

function department_update_submit_cancel($form, $form_state){
	drupal_goto('syllabus_main/departments');
}

function department_open() {
	drupal_set_message("Open");
}