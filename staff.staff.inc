<?php

// staff

function staff_page() {
	drupal_add_css('http://code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css', 'external');
	drupal_add_js('http://code.jquery.com/jquery-1.10.2.js', 'external');
	drupal_add_js('http://code.jquery.com/ui/1.11.4/jquery-ui.js', 'external');

	$years = db_query("SELECT DISTINCT year FROM {syllabus_main_course} WHERE year!=0 ORDER BY year ASC");

	$header = array(
		'course_name' => 'Course Name', 
		'course_teacher' => 'Teacher', 
		'course_status' => 'Status', 
		'button' => 'View'
		);
	$form = array();
	$x = "";

	foreach ($years as $year) {
		$a = $year -> year . " / " . ($year -> year + 1);
		$x .= "<li><a href='#" . $year -> year . "'>" . $a . "</a></li>";
	}

	$form["ax"] = array(
		'#markup' => '<div id="tabs"><ul>' . $x . '</ul>');

	$years = db_query("SELECT DISTINCT year FROM {syllabus_main_course} WHERE year!=0 ORDER BY year ASC");
	foreach ($years as $year) {
		global $user;
		$results = db_query("SELECT * FROM {syllabus_main_course} WHERE {coordinator}='" . $user -> uid . "' AND {year}=" . $year -> year);

		${'options' . $year -> year} = array();

		foreach ($results as $result) {
			$userx = db_query("SELECT * FROM {users} WHERE {uid}=" . $result -> coordinator . " LIMIT 1") -> fetchObject();
			if (isset($userx -> name)) {
				$teacher = $userx -> name;
			} else {
				$teacher = " / ";
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

			if ((($result -> status == 0) || ($result -> status == 2)) && ($year -> year >= date("Y"))) {
				${'options' . $year -> year}[$result -> id] = array(
					'id' => $result -> id,
					'course_name' => $result -> name,
					'course_teacher' => $teacher,
					'course_status' => $status,
					'button' => '<a href="' . base_path() . 'syllabus_main/staff_course?idx=' . $result -> id . '">Edit</a>'
					);
			} else {
				${'options' . $year -> year}[$result -> id] = array(
					'id' => $result -> id,
					'course_name' => $result -> name,
					'course_teacher' => $teacher,
					'course_status' => $status,
					'button' => '<a href="' . base_path() . 'syllabus_main/public_course?idx=' . $result -> id . '">View</a>'
					);
			}
		}

		$form['table'][$year -> year] = array(
			'#type' => 'tableselect',
			'#header' => $header,
			'#options' => ${'options' . $year -> year},
			'#prefix' => '<div id="' . $year -> year . '">',
			'#suffix' => '</div>',
			'#empty' => t('No courses found'),
			);
	}
	$form["bx"] = array(
		'#markup' => '</div><script> $(function() { $("#tabs").tabs(); }); </script>');

	return $form;
}
	// $form['radio'] = array(
	// 	'#type' => 'radios',
	// 	'#options' => $options,
	// 	'#prefix' => '<div id="tabs">
	// 	<ul>' . $x . '</ul>',
	// 	'#suffix' => '</div><script> $(function() { $("#tabs").tabs(); }); </script>',
	// 	);

	// $years = db_query("SELECT DISTINCT year FROM {syllabus_main_course} WHERE year!=0 ORDER BY year ASC");
	// foreach ($years as $year) {
	// 	global $user;
	// 	$results = db_query("SELECT * FROM {syllabus_main_course} WHERE {coordinator}='" . $user -> uid . "' AND {year}=" . $year -> year);

	// 	$i=1;
	// 	foreach ($results as $result) {
	// 		if ($results->rowCount() == 1) {
	// 			$form['table'][$year -> year][$result -> id] = array(
	// 				'#prefix' => '<div id="' . $year -> year . '">',
	// 				'#suffix' => '</div>'
	// 				);
	// 		} else {
	// 			if ($i == 1) {
	// 				$form['table'][$year -> year][$result -> id] = array(
	// 					'#prefix' => '<div id="' . $year -> year . '">'
	// 					);
	// 			}
	// 			if ($i == $results->rowCount()) {
	// 				$form['table'][$year -> year][$result -> id] = array(
	// 					'#suffix' => '</div>'
	// 					);
	// 			}
	// 		}
	// 		$i++;
	// 	}
	// }

	// $form['submit_edit'] = array(
	// 	'#type' => 'submit',
	// 	'#value' => t('Edit'),
	// 	'#submit' => array('staff_page_submit_edit'),
	// 	);
	// $form['submit_send'] = array(
	// 	'#type' => 'submit',
	// 	'#value' => t('Send'),
	// 	'#submit' => array('staff_page_submit_send'),
	// 	);



// function staff_page_submit_edit($form, $form_state) {
// 	if (isset($form_state['values']['radio'])) {
// 		drupal_goto('syllabus_main/staff_course', array('query' => array('idx' => $form_state['values']['radio'])));
// 	}
// }

// function staff_page_submit_send($form, $form_state) {
// 	if (isset($form_state['values']['radio'])) {
// 		if (db_query("UPDATE {syllabus_main_course} SET {status}=1 WHERE {id}=" . $form_state['values']['radio'])) {
// 			drupal_set_message('Sent!');
// 		}
// 	}
// }

