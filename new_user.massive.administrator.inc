<?php

//admin mass new user

function mass_new_user_page() {
	$form['titles'] = array(
		'#title' => t('Titles'), 
		'#type' => 'textarea', 
		'#description' => t('The comment will be unpublished'), 
		'#value' => isset(  $context['titles']) ? drupal_implode_tags($context['titles']) : '',);
	$form['fnames'] = array(
		'#title' => t('First Names'), 
		'#type' => 'textarea', 
		'#description' => t('The comment will be unpublished'), 
		'#value' => isset(  $context['fnames']) ? drupal_implode_tags($context['fnames']) : '',);
	$form['lnames'] = array(
		'#title' => t('Last Names'), 
		'#type' => 'textarea', 
		'#description' => t('The comment will be unpublished'), 
		'#value' => isset(  $context['lnames']) ? drupal_implode_tags($context['lnames']) : '',);
	$form['emails'] = array(
		'#title' => t('Email Adresses'), 
		'#type' => 'textarea', 
		'#description' => t('The comment will be unpublished'), 
		'#value' => isset(  $context['emails']) ? drupal_implode_tags($context['emails']) : '',);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Create Users',
		'#submit' => array('new_department_get_form'),
		);

	return $form;
}