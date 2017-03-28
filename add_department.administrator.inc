<?php

// admin new department

function new_department_page() {
	$users = db_query("SELECT * FROM {users}");

	$options = array();

	foreach ($users as $user) {
		$options[$user -> uid] = $user -> name;
	}

	$form['department_name'] = array(
		'#type' => 'textfield',
		'#title' => t("Department Name:"),
		'#required' => TRUE
		);
	$form['department_code'] = array(
		'#type' => 'textfield',
		'#title' => t("Department Code:"),
		'#required' => TRUE
		);
	$form['hod'] = array(
		'#type' => 'select',
		'#title' => t('Head of Department:'),
		'#options' => $options,
		'#description' => t('Select <em>Head of Department</em> for the new <em>Department</em>'),
		'#required' => TRUE
		);

	$form["submit"] = array(
		'#type' => 'submit',
		'#value' => 'Add Department');

	return $form;
}

function new_department_page_submit($form, $form_state){
	$id = db_insert('syllabus_main_department') -> fields(array(
		'department_name' => $form_state['values']['department_name'],
		'department_code' => $form_state['values']['department_code'],
		'hod' => $form_state['values']['hod'],
		)) -> execute();

	// $x = "Statystyka
	// Język obcy 1
	// W-f 1 / Sport i rekreacja 1
	// Statystyka
	// Metody badań społecznych
	// Analiza i generowanie informacji w języku angielskim 1
	// Seminarium licencjackie 1";

	// // $z = "";

	// // $w = explode("\n", $z);
	// $y = explode("\n", $x);
	// for ($i=0; $i < count($y); $i++) { 
	// 	$id = db_insert('syllabus_main_course') -> fields(array(
	// 		'name' => $y[$i],
	// 		'dep' => '15',
	// 		)) -> execute();
	// }

// $d = "";

// $f = explode("\n", $d);

// for ($i=0; $i < count($f); $i++) {
// 	// drupal_set_message(substr($f[$i], 0, 2));
// 	switch (substr($f[$i], 0, 2)) {
// 		case 'CI':
// 			$f[$i] = 1;
// 			break;
// 		case 'EC':
// 			$f[$i] = 8;
// 			break;
// 		case 'CE':
// 			$f[$i] = 6;
// 			break;
// 		case 'AR':
// 			$f[$i] = 4;
// 			break;
// 		case 'DI':
// 			$f[$i] = 7;
// 			break;
// 		case 'FA':
// 			$f[$i] = 10;
// 			break;
// 		case 'GE':
// 			$f[$i] = 11;
// 			break;
// 		case 'GR':
// 			$f[$i] = 12;
// 			break;
// 		case 'MN':
// 			$f[$i] = 14;
// 			break;
// 		case 'TO':
// 			$f[$i] = 17;
// 			break;
// 		case 'TP':
// 			$f[$i] = 18;
// 			break;
// 		case 'FL':
// 			$f[$i] = 20;
// 			break;
// 		case 'IR':
// 			$f[$i] = 21;
// 			break;
// 		case 'PE':
// 			$f[$i] = 22;
// 			break;
// 		case 'LI':
// 			$f[$i] = 23;
// 			break;
// 		case 'TR':
// 			$f[$i] = 24;
// 			break;
// 		case 'JO':
// 			$f[$i] = 25;
// 			break;
// 		case 'PH':
// 			$f[$i] = 26;
// 			break;
// 		case 'AU':
// 			$f[$i] = 27;
// 			break;
		
// 		default:
// 			$f[$i] = 28;
// 			break;
// 	}
// }
// $b = explode("\n", $a);
// $w = explode("\n", $z);
// $y = explode("\n", $x);
// 	for ($i=0; $i < count($y); $i++) {
// 		$pos = strpos($y[$i], '-') + 1;
// 		$y[$i] = substr($y[$i], $pos);

// 		// if (empty($y[$i])) {
// 		// 	$y[$i] = " ";
// 		// }
// 		// if (empty($b[$i])) {
// 		// 	$b[$i] = " ";
// 		// }
// 		// if (empty($w[$i])) {
// 		// 	$w[$i] = " ";
// 		// }

// 		$id = db_insert('syllabus_main_course') -> fields(array(
// 			'name' => $y[$i],
// 			'code' => $b[$i],
// 			'lang' => $w[$i],
// 			'dep' => $f[$i],
// 			)) -> execute();

// 		// drupal_set_message($f[$i]);
// 	}

	drupal_set_message('New Department has been added!');
}




