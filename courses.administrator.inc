<?php

//admin courses

function courses_page() {
	drupal_add_css('https://cdn.datatables.net/1.10.11/css/jquery.dataTables.min.css', 'external');
	drupal_add_js('https://code.jquery.com/jquery-1.12.0.min.js', 'external');
	drupal_add_js('https://cdn.datatables.net/1.10.11/js/jquery.dataTables.min.js', 'external');

	$results = db_query("SELECT * FROM {syllabus_main_course}");

	$header = array('course_name' => 'Course Name', 'course_teacher' => 'Teacher', 'department' => 'Department', 'course_status' => 'Status');
	$rows = array();

	foreach ($results as $result) {
		$teachers = db_query("SELECT * FROM {users} WHERE {uid}='" . $result -> teacher . "' LIMIT 1") -> fetchObject();
		if (!empty($teachers)) {
			$teacher = $teachers -> name . " / " . $teachers -> mail;
		} else {
			$teacher = " / ";
		}

		$departments = db_query("SELECT * FROM {syllabus_main_department} WHERE {id}='" . $result -> dep . "' LIMIT 1") -> fetchObject();
		if (!empty($departments)) {
			$department = $departments -> department_name . " / " . $departments -> department_code;
		} else {
			$department = " / ";
		}

		$status = "";
		if ($result -> status == 0) {
			$status = "In Progress";
		} else if ($result -> status == 1) {
			$status = "Pending";
		} else if ($result -> status == 2) {
			$status = "Declined";
		} else if ($result -> status == 3) {
			$status = "Approved";
		}

		$rows[$result -> id] = array(
			'id' => $result -> id,
			'course_name' => $result -> name,
			'course_teacher' => $teacher,
			'department' => $department,
			'course_status' => $status
			);
	}

	$options = array();
	foreach ($rows as $row) {
		$options[$row['id']] = array(
			'course_name' => $row['course_name'],
			'course_teacher' => $row['course_teacher'],
			'department' => $row['department'],
			'course_status' => $row['course_status']
			);
	}
	// var_dump($options);
	$form['table'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#suffix' => '<script>$(document).ready(function() { $("table").DataTable(); });</script>',
		'#empty' => t('No courses found'),
		);

	$form['submit_update'] = array(
		'#type' => 'submit',
		'#value' => t('Update'),
		'#submit' => array('courses_page_submit_update'),
		);
	$form['submit_delete'] = array(
		'#type' => 'submit',
		'#value' => t('Delete'),
		'#submit' => array('courses_page_submit_delete'),
		);

	return $form;
}

function courses_page_submit_update($form, $form_state){
	$x = 0;
	$y = 0;
	foreach ($form_state['values']['table'] as $value) {
		if ($value != 0) {
			$y = $value;
			$x++;
		}
	}
	if ($x == 1) {
		drupal_goto('syllabus_main/course_update', array('query' => array('idx' => $y)));
	} else if ($x > 1) {
		drupal_set_message("Please select just one!");
	} else if ($x < 1) {
		drupal_set_message("Please select one!");
	}
}

function courses_page_submit_delete($form, $form_state){
	$x = 0;
	foreach (($form_state['values']['table']) as $lines => $line) {
		if($line) {
			$x++;
			$delete = db_delete('syllabus_main_course')
			->condition('id', $line)
			-> execute();
		}
	}
	if ($x == 0) {
		drupal_set_message('No line selected!');
	}
}