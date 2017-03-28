<?php

function staff_course() {
  $css = "div#tabs2 [type=number] {
            width: 100px;
          }

          div#tabs2 textarea {
            width: 150px;
          }";
  drupal_add_css($css, 'inline');
	drupal_add_css('http://code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css', 'external');
  drupal_add_js('http://code.jquery.com/jquery-1.10.2.js', 'external');
  drupal_add_js('http://code.jquery.com/ui/1.11.4/jquery-ui.js', 'external');

  $idx = filter_input(INPUT_GET, 'idx');
  $course = db_query("SELECT * FROM {syllabus_main_course} WHERE {id}='" . $idx . "' LIMIT 1") -> fetchObject();
  $departmentx = db_query("SELECT {department_name} FROM {syllabus_main_department} WHERE {id}=" . $course -> dep . " LIMIT 1") -> fetchField();
  $coordinatorx = db_query("SELECT {name} FROM {users} WHERE {uid}=" . $course -> coordinator . " LIMIT 1") -> fetchField();
  $teachers = "";
  $teacherx = explode(";", $course -> teacher);
  for ($i=1; $i < (count($teacherx) - 1); $i++) {
    $xx = db_query("SELECT * FROM {users} WHERE {uid}=" . $teacherx[$i] . " LIMIT 1") -> fetchObject();
    $teachers .= "\"" . $xx -> name . " / " . $xx -> mail . "\", ";
  }

  $results = db_query("SELECT * FROM {syllabus_main_course}");
  $departments = db_query("SELECT * FROM {syllabus_main_department}");
  $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");
  $preres = db_query("SELECT * FROM {syllabus_main_prerequisites}");
  $objectives = db_query("SELECT * FROM {syllabus_main_objective}");
  $assmeths = db_query("SELECT * FROM {syllabus_main_assmeth}");
  $users = db_query("SELECT * FROM {users}");
  $teacher = db_query("SELECT * FROM {users} WHERE {uid}='" . $idx . "' LIMIT 1") -> fetchObject();
  // $years = db_query("SELECT DISTINCT year FROM {syllabus_main_course}");
  $years = array("2014", "2015", "2016", "2017");
  $languages = array("English", "Polish");
  $methods = array("Lecture", "Lecture and practical classes", "Discussion session", "Labaratory classes", "Seminar", "Workshops", "E-learning");
  $levels = array("First Level", "Second Level", "Postgraduate");
  $modes = array("Full Time", "Part Time");
  $profiles = array("General Academic", "Professional Profile");

  $i = 0;
  $course_code = "";
  // $course_year = "<option value='2014'>2014<br/><option value='2015'>2015<br/><option value='2016'>2016<br/><option value='2017'>2017<br/>";
  $course_year = "";
  $course_dep ="";
  $course_dep_2 ="";
  $course_coordinator = "";
  $course_teacher = "";
  $course_teacher2 = "";
  $course_teacher3 = "";
  $prere = "";
  $prere2 = "";
  $prere3 = "";
  $current_year = "";
  $course_lang = "";
  $course_level = "";
  $course_mode = "";
  $course_profile = "";
  $course_objectives = "";
  $course_note = "";
  $course_assmethx = "";
  $course_w_assmeth_x = array();
  $course_u_assmeth_x = array();
  $course_k_assmeth_x = array();

  $course_w_code_x = "";
  $course_u_code_x = "";
  $course_k_code_x = "";
  $course_code_empty = "";

  $course_w_outcomes = explode(";", $course -> w_outcome);
  $course_w_assmeth = explode(";", $course -> w_assmeth);
  $course_w_code = explode(";", $course -> w_code);
  $course_u_outcomes = explode(";", $course -> u_outcome);
  $course_u_assmeth = explode(";", $course -> u_assmeth);
  $course_u_code = explode(";", $course -> u_code);
  $course_k_outcomes = explode(";", $course -> k_outcome);
  $course_k_assmeth = explode(";", $course -> k_assmeth);
  $course_k_code = explode(";", $course -> k_code);

  $course_lecture = explode(";", $course -> lecture);
  $course_lab = explode(";", $course -> lab);
  $course_discussion = explode(";", $course -> discussion);
  $course_seminar = explode(";", $course -> seminar);
  $course_workshop = explode(";", $course -> workshop);
  $course_elearning = explode(";", $course -> elearning);
  $course_lec_other = explode(";", $course -> lec_other);

  $course_percent = explode(";", $course -> percent);

  $course_other_name = explode(";", $course -> other_name);
  $course_other = explode(";", $course -> other);
  $course_ws_hour = explode(";", $course -> ws_hour);
  $course_ws_activity = explode(";", $course -> ws_activity);
  $course_ws_hour2 = explode(";", $course -> ws_non_con_hour);

  foreach ($codes as $code) {
    $course_code_empty .= "<option value='" . $code -> id . "'>" . $code -> code . " / " . $code -> description . "<br/>";
  }

  $course_w_assmeth_xx = "";
  $course_u_assmeth_xx = "";
  $course_k_assmeth_xx = "";
  foreach ($assmeths as $assmeth) {
    if ($course_w_assmeth[0] == $assmeth -> id) {
      $course_w_assmeth_xx .= "<option value='" . $assmeth -> id . "' selected>" . $assmeth -> name . "<br/>";
    } else {
      $course_w_assmeth_xx .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";
    }

    if ($course_u_assmeth[0] == $assmeth -> id) {
      $course_u_assmeth_xx .= "<option value='" . $assmeth -> id . "' selected>" . $assmeth -> name . "<br/>";
    } else {
      $course_u_assmeth_xx .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";
    }

    if ($course_k_assmeth[0] == $assmeth -> id) {
      $course_k_assmeth_xx .= "<option value='" . $assmeth -> id . "' selected>" . $assmeth -> name . "<br/>";
    } else {
      $course_k_assmeth_xx .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";
    }
  }
  array_push($course_w_assmeth_x, $course_w_assmeth_xx);
  array_push($course_u_assmeth_x, $course_u_assmeth_xx);
  array_push($course_k_assmeth_x, $course_k_assmeth_xx);

// knowledge
  $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");
  $code_xw = "";
  foreach ($codes as $code) {
    if ($course_w_code[0] == $code -> id) {
      $course_w_code_x .= "<option value='" . $code -> id . "' selected>" . $code -> code . " / " . $code -> description . "<br/>";
      $code_xw = $code -> code;
    } else {
      $course_w_code_x .= "<option value='" . $code -> id . "'>" . $code -> code . " / " . $code -> description . "<br/>";
    }
  }

  $course_knowledge = "<div id='dialogw1' title='Code Description'><form><select id='W1_codex' name='W_codex[]'>" . $course_w_code_x . "</select><input type=\'button\' value=\'Ok\' onclick=\'close_dialog1(1);\'></form></div><table class=\'table table-bordered table-hover\'><tr><td>W1</td><td><input type=\'hidden\' id=\'W1_code\' name=\'W_code[]\' value=\'" . $course_w_code[0] . "\'><textarea id=\'W_outcomes[]\' name=\'W_outcomes[]\'>" . $course_w_outcomes[0] . "</textarea></td><td><select id=\'W1_assmeths\' name=\'W1_assmeths\'  onchange=\'knowledge_onblur(1)\'>" . $course_w_assmeth_x[0] . "</select></td><td><form><input type='button' onclick='dialog1(1);' value='Code'></form></td><td><p id=\'labelw_1\'>" . $code_xw . "</p></td><td><form><input type='button' onclick='knowledge();' value='Add more'></form></td></tr></table>";

  $course_dialog = "$('#dialogw1').dialog({ autoOpen: false, show: { effect: 'blind', duration: 500 }, height:'auto', width:'90%' });";

  for ($i=1; $i < (count($course_w_outcomes) - 1); $i++) {
    $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");

    $code_xw = "";
    $course_w_code_x = "";
    foreach ($codes as $code) {
      if ($course_w_code[$i] == $code -> id) {
        $course_w_code_x .= "<option value='" . $code -> id . "' selected>" . $code -> code . " / " . $code -> description . "<br/>";
        $code_xw = $code -> code;
      } else {
        $course_w_code_x .= "<option value='" . $code -> id . "'>" . $code -> code . " / " . $code -> description . "<br/>";
      }
    }

    $assmeths = db_query("SELECT * FROM {syllabus_main_assmeth}");

    $course_w_assmeth_xy = "";
    foreach ($assmeths as $assmeth) {
      if ($course_w_assmeth[$i] == $assmeth -> id) {
        $course_w_assmeth_xy .= "<option value='" . $assmeth -> id . "' selected>" . $assmeth -> name . "<br/>";
      } else {
        $course_w_assmeth_xy .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";
      }
    }
    array_push($course_w_assmeth_x, $course_w_assmeth_xy);

    $course_knowledge .= "<div id='dialogw" . ($i + 1) . "' title='Code Description'><form><select id='W" . ($i + 1) . "_codex' name='W_codex[]'>" . $course_w_code_x . "</select><input type=\'button\' value=\'Ok\' onclick=\'close_dialog1(" . ($i + 1) . ", &quot;" . $code_xw . "&quot;);\'></form></div><table class=\'table table-bordered table-hover\'><tr><td>W" . ($i + 1) . "</td><td><input type=\'hidden\' id=\'W" . ($i + 1) . "_code\' name=\'W_code[]\' value=\'" . $course_w_code[$i] . "\'><textarea id=\'W_outcomes[]\' name=\'W_outcomes[]\'>" . $course_w_outcomes[$i] . "</textarea></td><td><select id=\'W" . ($i + 1) . "_assmeths\' name=\'W" . ($i + 1) . "_assmeths\'  onchange=\'knowledge_onblur(" . ($i + 1) . ")\'>" . $course_w_assmeth_x[$i] . "</select></td><td><form><input type='button' onclick='dialog1(" . ($i + 1) . ");' value='Code'></form></td><td><p id=\'labelw_" . ($i + 1) . "\'>" . $code_xw . "</p></td></tr></table>";

    $course_dialog .= "$('#dialogw" . ($i + 1) . "').dialog({ autoOpen: false, show: { effect: 'blind', duration: 500 }, height:'auto', width:'90%' });";
  }

// skill
  $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");
  $code_xu = "";
  foreach ($codes as $code) {
    if ($course_u_code[0] == $code -> id) {
      $course_u_code_x .= "<option value='" . $code -> id . "' selected>" . $code -> code . " / " . $code -> description . "<br/>";
      $code_xu = $code -> code;
    } else {
      $course_u_code_x .= "<option value='" . $code -> id . "'>" . $code -> code . " / " . $code -> description . "<br/>";
    }
  }

  $course_skill = "<div id='dialogu1' title='Code Description'><form><select id='U1_codex' name='U_codex[]'>" . $course_u_code_x . "</select><input type='button' value='Ok' onclick='close_dialog2(1);'></form></div><table class=\'table table-bordered table-hover\'><tr><td>U1</td><td><input type=\'hidden\' id=\'U1_code\' name=\'U_code[]\' value=\'" . $course_u_code[0] . "\'><textarea id=\'U_outcomes[]\' name=\'U_outcomes[]\'>" . $course_u_outcomes[0] . "</textarea></td><td><select id=\'U1_assmeths\' name=\'U1_assmeths\'  onchange=\'skill_onblur(1)\'>" . $course_u_assmeth_x[0] . "</select></td><td><form><input type='button' onclick='dialog2(1);' value='Code'></form></td><td><p id=\'labelu_1\'>" . $code_xu . "</p></td><td><form><input type='button' onclick='skill();' value='Add more'></form></td></tr></table>";

  $course_dialog2 = "$('#dialogu1').dialog({ autoOpen: false, show: { effect: 'blind', duration: 500 }, height:'auto', width:'90%' });";

  for ($i=1; $i < (count($course_u_outcomes) - 1); $i++) {
    $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");

    $code_xu = "";
    $course_u_code_x = "";
    foreach ($codes as $code) {
      if ($course_u_code[$i] == $code -> id) {
        $course_u_code_x .= "<option value='" . $code -> id . "' selected>" . $code -> code . " / " . $code -> description . "<br/>";
        $code_xu = $code -> code;
      } else {
        $course_u_code_x .= "<option value='" . $code -> id . "'>" . $code -> code . " / " . $code -> description . "<br/>";
      }
    }

    $assmeths = db_query("SELECT * FROM {syllabus_main_assmeth}");

    $course_u_assmeth_xy = "";
    foreach ($assmeths as $assmeth) {
      if ($course_u_assmeth[$i] == $assmeth -> id) {
        $course_u_assmeth_xy .= "<option value='" . $assmeth -> id . "' selected>" . $assmeth -> name . "<br/>";
      } else {
        $course_u_assmeth_xy .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";
      }
    }
    array_push($course_u_assmeth_x, $course_u_assmeth_xy);

    $course_skill .= "<div id='dialogu" . ($i + 1) . "' title='Code Description'><form><select id='U" . ($i + 1) . "_codex' name='U_codex[]'>" . $course_u_code_x . "</select><input type='button' value='Ok' onclick='close_dialog2(" . ($i + 1) . ");'></form></div><table class=\'table table-bordered table-hover\'><tr><td>U" . ($i + 1) . "</td><td><input type=\'hidden\' id=\'U" . ($i + 1) . "_code\' name=\'U_code[]\' value=\'" . $course_u_code[$i] . "\'><textarea id=\'U_outcomes[]\' name=\'U_outcomes[]\'>" . $course_u_outcomes[$i] . "</textarea></td><td><select id=\'U" . ($i + 1) . "_assmeths\' name=\'U" . ($i + 1) . "_assmeths\'  onchange=\'skill_onblur(" . ($i + 1) . ")\'>" . $course_u_assmeth_x[$i] . "</select></td><td><form><input type='button' onclick='dialog2(" . ($i + 1) . ");' value='Code'></form></td><td><p id=\'labelu_" . ($i + 1) . "\'>" . $code_xu . "</p></td></tr></table>";

    $course_dialog2 .= "$('#dialogu" . ($i + 1) . "').dialog({ autoOpen: false, show: { effect: 'blind', duration: 500 }, height:'auto', width:'90%' });";
  }

// social
  $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");
  $code_xk = "";
  foreach ($codes as $code) {
    if ($course_k_code[0] == $code -> id) {
      $course_k_code_x .= "<option value='" . $code -> id . "' selected>" . $code -> code . " / " . $code -> description . "<br/>";
      $code_xk = $code -> code;
    } else {
      $course_k_code_x .= "<option value='" . $code -> id . "'>" . $code -> code . " / " . $code -> description . "<br/>";
    }
  }

  $course_social = "<div id='dialogk1' title='Code Description'><form><select id='K1_codex' name='K_codex[]'>" . $course_k_code_x . "</select><input type='button' value='Ok' onclick='close_dialog3(1);'></form></div><table class=\'table table-bordered table-hover\'><tr><td>K1</td><td><input type=\'hidden\' id=\'K1_code\' name=\'K_code[]\' value=\'" . $course_k_code[0] . "\'><textarea id=\'K_outcomes[]\' name=\'K_outcomes[]\'>" . $course_k_outcomes[0] . "</textarea></td><td><select id=\'K1_assmeths\' name=\'K1_assmeths\'  onchange=\'social_onblur(1)\'>" . $course_k_assmeth_x[0] . "</select></td><td><form><input type='button' onclick='dialog3(1);' value='Code'></form></td><td><p id=\'labelk_1\'>" . $code_xk . "</p></td><td><form><input type='button' onclick='social();' value='Add more'></form></td></tr></table>";

  $course_dialog3 = "$('#dialogk1').dialog({ autoOpen: false, show: { effect: 'blind', duration: 500 }, height:'auto', width:'90%' });";

  for ($i=1; $i < (count($course_k_outcomes) - 1); $i++) {
    $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");
    
    $code_xk = "";
    $course_k_code_x = "";
    foreach ($codes as $code) {
      if ($course_k_code[$i] == $code -> id) {
        $course_k_code_x .= "<option value='" . $code -> id . "' selected>" . $code -> code . " / " . $code -> description . "<br/>";
        $code_xk = $code -> code;
      } else {
        $course_k_code_x .= "<option value='" . $code -> id . "'>" . $code -> code . " / " . $code -> description . "<br/>";
      }
    }

    $assmeths = db_query("SELECT * FROM {syllabus_main_assmeth}");

    $course_k_assmeth_xy = "";
    foreach ($assmeths as $assmeth) {
      if ($course_k_assmeth[$i] == $assmeth -> id) {
        $course_k_assmeth_xy .= "<option value='" . $assmeth -> id . "' selected>" . $assmeth -> name . "<br/>";
      } else {
        $course_k_assmeth_xy .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";
      }
    }
    array_push($course_k_assmeth_x, $course_k_assmeth_xy);

    $course_social .= "<div id='dialogk" . ($i + 1) . "' title='Code Description'><form><select id='K" . ($i + 1) . "_codex' name='K_codex[]'>" . $course_k_code_x . "</select><input type='button' value='Ok' onclick='close_dialog3(" . ($i + 1) . ");'></form></div><table class=\'table table-bordered table-hover\'><tr><td>K" . ($i + 1) . "</td><td><input type=\'hidden\' id=\'K" . ($i + 1) . "_code\' name=\'K_code[]\' value=\'" . $course_k_code[$i] . "\'><textarea id=\'K_outcomes[]\' name=\'K_outcomes[]\'>" . $course_k_outcomes[$i] . "</textarea></td><td><select id=\'K" . ($i + 1) . "_assmeths\' name=\'K" . ($i + 1) . "_assmeths\'  onchange=\'social_onblur(" . ($i + 1) . ")\'>" . $course_k_assmeth_x[$i] . "</select></td><td><form><input type='button' onclick='dialog3(" . ($i + 1) . ");' value='Code'></form></td><td><p id=\'labelk_" . ($i + 1) . "\'>" . $code_xk . "</p></td></tr></table>";

    $course_dialog3 .= "$('#dialogk" . ($i + 1) . "').dialog({ autoOpen: false, show: { effect: 'blind', duration: 500 }, height:'auto', width:'90%' });";
  }

// ass meth
  $course_assmeths = "";
  $j = 0;
  for ($i=0; $i < (count($course_w_assmeth) - 1); $i++) {
    if (empty($course_w_assmeth[$i])) {
      $course_assmeths .= "<table class=\'table table-bordered table-hover\' id=\'w" . ($i + 1) . "\'><tr><td></td><td colspan=\'2\'></td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>";
      $j++;
    } else {
      $xx = db_query("SELECT * FROM {syllabus_main_assmeth} WHERE {id}='" . $course_w_assmeth[$i] . "' LIMIT 1") -> fetchObject();
      $course_assmeths .= "<table class=\'table table-bordered table-hover\' id=\'w" . ($i + 1) . "\'><tr><td></td><td colspan=\'2\'>" . $xx -> name . "</td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\' value=\'" . $course_percent[$j] . "\'></td></tr></table>";
      $j++;
    }
  }
  for ($i=0; $i < (count($course_u_assmeth) - 1); $i++) {
    if (empty($course_u_assmeth[$i])) {
      $course_assmeths .= "<table class=\'table table-bordered table-hover\' id=\'u" . ($i + 1) . "\'><tr><td></td><td colspan=\'2\'></td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>";
      $j++;
    } else {
      $xx = db_query("SELECT * FROM {syllabus_main_assmeth} WHERE {id}='" . $course_u_assmeth[$i] . "' LIMIT 1") -> fetchObject();
      $course_assmeths .= "<table class=\'table table-bordered table-hover\' id=\'u" . ($i + 1) . "\'><tr><td></td><td colspan=\'2\'>" . $xx -> name . "</td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\' value=\'" . $course_percent[$j] . "\'></td></tr></table>";
      $j++;
    }
  }
  for ($i=0; $i < (count($course_k_assmeth) - 1); $i++) {
    if (empty($course_k_assmeth[$i])) {
      $course_assmeths .= "<table class=\'table table-bordered table-hover\' id=\'k" . ($i + 1) . "\'><tr><td></td><td colspan=\'2\'></td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>";
      $j++;
    } else {
      $xx = db_query("SELECT * FROM {syllabus_main_assmeth} WHERE {id}='" . $course_k_assmeth[$i] . "' LIMIT 1") -> fetchObject();
      $course_assmeths .= "<table class=\'table table-bordered table-hover\' id=\'k" . ($i + 1) . "\'><tr><td></td><td colspan=\'2\'>" . $xx -> name . "</td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\' value=\'" . $course_percent[$j] . "\'></td></tr></table>";
      $j++;
    }
  }


// lecture
  $course_lectures = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_lecture\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'lecture[]\' id=\'lecture0\' onblur=\'lec_onblur(0)\'>" . $course_lecture[0] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_lecture0\' name=\'ws_hour[]\' onblur=\'lecture_onblur()\' value='" . $course_ws_hour[0] . "'> h</td><td><input type=\'number\' id=\'ws_hour_lecture20\' name=\'ws_hour2[]\' onblur=\'lecture_onblur()\' value='" . $course_ws_hour2[0] . "'> h</td><td><form><input type=\'button\' onclick=\'lectures()\' value=\'Add more\'></form></td></tr></table>";

  for ($i=1; $i < (count($course_lecture) - 1); $i++) {
    $course_lectures .= "<table class=\'table table-bordered table-hover\'><tr><td>Topic " . ($i + 1) . ":</td><td><textarea name=\'lecture[]\' id=\'lecture" . $i . "\' onblur=\'lec_onblur(" . $i . ")\'>" . $course_lecture[$i] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_lecture" . $i . "\' name=\'ws_hour[]\' onblur=\'lecture_onblur()\' value='" . $course_ws_hour[$i] . "'> h</td><td><input type=\'number\' id=\'ws_hour_lecture2" . $i . "\' name=\'ws_hour2[]\' onblur=\'lecture_onblur()\' value='" . $course_ws_hour2[$i] . "'> h</td></tr></table>";
  }

// lab
  $course_labs = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_lab\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'lab[]\' id=\'lab0\' onblur=\'lab_onblur(0)\'>" . $course_lab[0] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_lab0\' name=\'ws_hour[]\' onblur=\'lab_onblur()\' value='" . $course_ws_hour[0] . "'> h</td><td><input type=\'number\' id=\'ws_hour_lab20\' name=\'ws_hour2[]\' onblur=\'lab_onblur()\' value='" . $course_ws_hour2[0] . "'> h</td><td><form><input type=\'button\' onclick=\'labs()\' value=\'Add more\'></form></td></tr></table>";

  for ($i=1; $i < (count($course_lab) - 1); $i++) {
    $course_labs .= "<table class=\'table table-bordered table-hover\'><tr><td>Topic " . ($i + 1) . ":</td><td><textarea name=\'lab[]\' id=\'lab" . $i . "\' onblur=\'lab_onblur(" . $i . ")\'>" . $course_lab[$i] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_lab" . $i . "\' name=\'ws_hour[]\' onblur=\'lab_onblur()\' value='" . $course_ws_hour[$i] . "'> h</td><td><input type=\'number\' id=\'ws_hour_lab2" . $i . "\' name=\'ws_hour2[]\' onblur=\'lab_onblur()\' value='" . $course_ws_hour2[$i] . "'> h</td></tr></table>";
  }

// discussion
  $course_discussions = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_discussion\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'discussion[]\' id=\'discussion0\' onblur=\'discussion_onblur(0)\'>" . $course_discussion[0] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_discussion0\' name=\'ws_hour[]\' onblur=\'discussion_onblur()\' value='" . $course_ws_hour[0] . "'> h</td><td><input type=\'number\' id=\'ws_hour_discussion20\' name=\'ws_hour2[]\' onblur=\'discussion_onblur()\' value='" . $course_ws_hour2[0] . "'> h</td><td><form><input type=\'button\' onclick=\'discussions()\' value=\'Add more\'></form></td></tr></table>";

  for ($i=1; $i < (count($course_discussion) - 1); $i++) {
    $course_discussions .= "<table class=\'table table-bordered table-hover\'><tr><td>Topic " . ($i + 1) . ":</td><td><textarea name=\'discussion[]\' id=\'discussion" . $i . "\' onblur=\'discussion_onblur(" . $i . ")\'>" . $course_discussion[$i] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_discussion" . $i . "\' name=\'ws_hour[]\' onblur=\'discussion_onblur()\' value='" . $course_ws_hour[$i] . "'> h</td><td><input type=\'number\' id=\'ws_hour_discussion2" . $i . "\' name=\'ws_hour2[]\' onblur=\'discussion_onblur()\' value='" . $course_ws_hour2[$i] . "'> h</td></tr></table>";
  }

// seminar
  $course_seminars = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_seminar\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'seminar[]\' id=\'seminar0\' onblur=\'seminar_onblur(0)\'>" . $course_seminar[0] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_seminar0\' name=\'ws_hour[]\' onblur=\'seminar_onblur()\' value='" . $course_ws_hour[0] . "'> h</td><td><input type=\'number\' id=\'ws_hour_seminar20\' name=\'ws_hour2[]\' onblur=\'seminar_onblur()\' value='" . $course_ws_hour2[0] . "'> h</td><td><form><input type=\'button\' onclick=\'seminars()\' value=\'Add more\'></form></td></tr></table>";

  for ($i=1; $i < (count($course_seminar) - 1); $i++) {
    $course_seminars .= "<table class=\'table table-bordered table-hover\'><tr><td>Topic " . ($i + 1) . ":</td><td><textarea name=\'seminar[]\' id=\'seminar" . $i . "\' onblur=\'seminar_onblur(" . $i . ")\'>" . $course_seminar[$i] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_seminar" . $i . "\' name=\'ws_hour[]\' onblur=\'seminar_onblur()\' value='" . $course_ws_hour[$i] . "'> h</td><td><input type=\'number\' id=\'ws_hour_seminar2" . $i . "\' name=\'ws_hour2[]\' onblur=\'seminar_onblur()\' value='" . $course_ws_hour2[$i] . "'> h</td></tr></table>";
  }

// workshop
  $course_workshops = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_workshop\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'workshop[]\' id=\'workshop0\' onblur=\'workshop_onblur(0)\'>" . $course_workshop[0] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_workshop0\' name=\'ws_hour[]\' onblur=\'workshop_onblur()\' value='" . $course_ws_hour[0] . "'> h</td><td><input type=\'number\' id=\'ws_hour_workshop20\' name=\'ws_hour2[]\' onblur=\'workshop_onblur()\' value='" . $course_ws_hour2[0] . "'> h</td><td><form><input type=\'button\' onclick=\'workshops()\' value=\'Add more\'></form></td></tr></table>";

  for ($i=1; $i < (count($course_workshop) - 1); $i++) {
    $course_workshops .= "<table class=\'table table-bordered table-hover\'><tr><td>Topic " . ($i + 1) . ":</td><td><textarea name=\'workshop[]\' id=\'workshop" . $i . "\' onblur=\'workshop_onblur(" . $i . ")\'>" . $course_workshop[$i] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_workshop" . $i . "\' name=\'ws_hour[]\' onblur=\'workshop_onblur()\' value='" . $course_ws_hour[$i] . "'> h</td><td><input type=\'number\' id=\'ws_hour_workshop2" . $i . "\' name=\'ws_hour2[]\' onblur=\'workshop_onblur()\' value='" . $course_ws_hour2[$i] . "'> h</td></tr></table>";
  }

// elearning
  $course_elearnings = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_elearning\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'elearning[]\' id=\'elearning0\' onblur=\'elearning_onblur(0)\'>" . $course_elearning[0] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_elearning0\' name=\'ws_hour[]\' onblur=\'elearning_onblur()\' value='" . $course_ws_hour[0] . "'> h</td><td><input type=\'number\' id=\'ws_hour_elearning20\' name=\'ws_hour2[]\' onblur=\'elearning_onblur()\' value='" . $course_ws_hour2[0] . "'> h</td><td><form><input type=\'button\' onclick=\'elearnings()\' value=\'Add more\'></form></td></tr></table>";

  for ($i=1; $i < (count($course_elearning) - 1); $i++) {
    $course_elearnings .= "<table class=\'table table-bordered table-hover\'><tr><td>Topic " . ($i + 1) . ":</td><td><textarea name=\'elearning[]\' id=\'elearning" . $i . "\' onblur=\'elearning_onblur(" . $i . ")\'>" . $course_elearning[$i] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_elearning" . $i . "\' name=\'ws_hour[]\' onblur=\'elearning_onblur()\' value='" . $course_ws_hour[$i] . "'> h</td><td><input type=\'number\' id=\'ws_hour_elearning2" . $i . "\' name=\'ws_hour2[]\' onblur=\'elearning_onblur()\' value='" . $course_ws_hour2[$i] . "'> h</td></tr></table>";
  }

// lec_other
  $course_lec_others = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_other\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'lec_other[]\' id=\'lec_other0\' onblur=\'lec_other_onblur(0)\'>" . $course_lec_other[0] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_other0\' name=\'ws_hour[]\' onblur=\'other_onblur()\' value='" . $course_ws_hour[0] . "'> h</td><td><input type=\'number\' id=\'ws_hour_other20\' name=\'ws_hour2[]\' onblur=\'other_onblur()\' value='" . $course_ws_hour2[0] . "'> h</td><td><form><input type=\'button\' onclick=\'lec_others()\' value=\'Add more\'></form></td></tr></table>";

  for ($i=1; $i < (count($course_lec_other) - 1); $i++) {
    $course_lec_others .= "<table class=\'table table-bordered table-hover\'><tr><td>Topic " . ($i + 1) . ":</td><td><textarea name=\'lec_other[]\' id=\'lec_other" . $i . "\' onblur=\'lec_other_onblur(" . $i . ")\'>" . $course_lec_other[$i] . "</textarea></td><td><input type=\'number\' id=\'ws_hour_other" . $i . "\' name=\'ws_hour[]\' onblur=\'other_onblur()\' value='" . $course_ws_hour[$i] . "'> h</td><td><input type=\'number\' id=\'ws_hour_other2" . $i . "\' name=\'ws_hour2[]\' onblur=\'other_onblur()\' value='" . $course_ws_hour2[$i] . "'> h</td></tr></table>";
  }

// reading
  $course_readings = "";
  for ($i=0; $i < (count($course_other) - 1); $i++) {
    $course_readings .= "<table class=\'table table-bordered table-hover\'><tbody><tr><td>C." . ($i + 3) . "</td><td><input type=\'text\' id=\'other_name[]\' name=\'other_name[]\' value='" . $course_other_name[$i] . "'></td><td><textarea id=\'other[]\' name=\'other[]\' style=\'height: 70px; width: 250px;\'>" . $course_other[$i] . "</textarea></td><td></td><td></td><td></td><td></td></tr></tbody></table>";
  }

// workload structure
  // $course_workloads = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td><input type=\'text\' name=\'ws_activity[]\' value='" . $course_ws_activity[0] . "'></td><td><input type=\'text\' id=\'ws_hour0\' name=\'ws_hour[]\' onblur=\'workload_onblur()\' value='" . $course_ws_hour[0] . "'> h</td><td><input type=\'text\' id=\'ws_hour20\' name=\'ws_hour2[]\' onblur=\'workload_onblur()\' value='" . $course_ws_hour2[0] . "'> h</td><td><form><input type=\'button\' onclick=\'workloadw()\' value=\'Add more\'></form></td></tr></tbody></table>";

  // for ($i=1; $i < (count($course_ws_hour) - 1); $i++) {
  //   $course_workloads .= "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td><input type=\'text\' name=\'ws_activity[]\' value='" . $course_ws_activity[$i] . "'></td><td><input type=\'text\' id=\'ws_hour" . $i . "\' name=\'ws_hour[]\' onblur=\'workload_onblur()\' value='" . $course_ws_hour[$i] . "'> h</td><td><input type=\'text\' id=\'ws_hour2" . $i . "\' name=\'ws_hour2[]\' onblur=\'workload_onblur()\' value='" . $course_ws_hour2[$i] . "'> h</td></tr></tbody></table>";
  // }

  $assmeths = db_query("SELECT * FROM {syllabus_main_assmeth}");

  foreach ($assmeths as $assmeth) {
    $course_assmethx .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";
  }

  if (!empty($course -> note)) {
    $course_note = $course -> note;
  } else {
    $course_note = "No new note from Head of Program.";
  }

  foreach ($objectives as $objective) {
    $xx = explode(";", $course -> objective);
    if (in_array($objective -> id, $xx)) {
      $course_objectives .= "<option value='" . $objective -> id . "' selected>" . $objective -> name . "<br/>";
    } else {
      $course_objectives .= "<option value='" . $objective -> id . "'>" . $objective -> name . "<br/>";
    }
  }

  foreach ($profiles as $profile) {
    if ($profile == $course -> degree) {
      $course_profile .= "<option value='" . $profile . "' selected>" . $profile . "<br/>";
    } else {
      $course_profile .= "<option value='" . $profile . "'>" . $profile . "<br/>";
    }
  }
  foreach ($modes as $mode) {
    if ($mode == $course -> mode) {
      $course_mode .= "<option value='" . $mode . "' selected>" . $mode . "<br/>";
    } else {
      $course_mode .= "<option value='" . $mode . "'>" . $mode . "<br/>";
    }
  }
  foreach ($levels as $level) {
    if ($level == $course -> level) {
      $course_level .= "<option value='" . $level . "' selected>" . $level . "<br/>";
    } else {
      $course_level .= "<option value='" . $level . "'>" . $level . "<br/>";
    }
  }
  foreach ($languages as $language) {
    if ($language == $course -> lang) {
      $course_lang .= "<option value='" . $language . "' selected>" . $language . "<br/>";
    } else {
      $course_lang .= "<option value='" . $language . "'>" . $language . "<br/>";
    }
  }
  foreach ($departments as $department) {
    if ($department -> id == $course -> dep) {
      $course_dep .= "<option value='" . $department -> id . "' selected>" . $department -> department_name . "<br/>";
    } else {
      $course_dep .= "<option value='" . $department -> id . "'>" . $department -> department_name . "<br/>";
    }
    if ($department -> id == $course -> field) {
      $course_dep_2 .= "<option value='" . $department -> id . "' selected>" . $department -> department_name . "<br/>";
    } else {
      $course_dep_2 .= "<option value='" . $department -> id . "'>" . $department -> department_name . "<br/>";
    }
  }
  foreach ($users as $user) {
    $xx = explode(";", $course -> teacher);
    if ($user -> uid == $xx[0]) {
      $course_teacher .= "<option value='" . $user -> uid . "' selected>" . $user -> name . " / " . $user -> mail . "<br/>";
    } else {
      $course_teacher .= "<option value='" . $user -> uid . "'>" . $user -> name . " / " . $user -> mail . "<br/>";
    }
    if ($user -> uid == $xx[1]) {
      $course_teacher2 .= "<option value='" . $user -> uid . "' selected>" . $user -> name . " / " . $user -> mail . "<br/>";
    } else {
      $course_teacher2 .= "<option value='" . $user -> uid . "'>" . $user -> name . " / " . $user -> mail . "<br/>";
    }
    if ($user -> uid == $xx[2]) {
      $course_teacher3 .= "<option value='" . $user -> uid . "' selected>" . $user -> name . " / " . $user -> mail . "<br/>";
    } else {
      $course_teacher3 .= "<option value='" . $user -> uid . "'>" . $user -> name . " / " . $user -> mail . "<br/>";
    }
    if ($user -> uid == $course -> coordinator) {
      $course_coordinator .= "<option value='" . $user -> uid . "' selected>" . $user -> name . "<br/>";
    } else {
      $course_coordinator .= "<option value='" . $user -> uid . "'>" . $user -> name . "<br/>";
    }
  }
  foreach ($results as $result) {
    if ($result -> code == $course -> code) {
      if (!empty($result -> code)) {
        $course_code .= "<option value='" . $result -> code . "' selected>" . $result -> code . "<br/>";
      } else {
        $course_code .= "<option value=''><br/>";
      }
    } else {
      if (!empty($result -> code)) {
        $course_code .= "<option value='" . $result -> code . "'>" . $result -> code . "<br/>";
      } else {
        $course_code .= "<option value=''><br/>";
      }
    }
    $i++;
  }
  foreach ($preres as $prerex) {
    if ($prerex -> id == $course -> prere) {
      $prere .= "<option value='" . $prerex -> id . "' selected>" . $prerex -> name . "<br/>";
    } else {
      $prere .= "<option value='" . $prerex -> id . "'>" . $prerex -> name . "<br/>";
    }
    if ($prerex -> id == $course -> prere2) {
      $prere2 .= "<option value='" . $prerex -> id . "' selected>" . $prerex -> name . "<br/>";
    } else {
      $prere2 .= "<option value='" . $prerex -> id . "'>" . $prerex -> name . "<br/>";
    }
    if ($prerex -> id == $course -> prere3) {
      $prere3 .= "<option value='" . $prerex -> id . "' selected>" . $prerex -> name . "<br/>";
    } else {
      $prere3 .= "<option value='" . $prerex -> id . "'>" . $prerex -> name . "<br/>";
    }
  }
  foreach ($years as $year) {
    if ($year == $course -> year) {
      $course_year .= "<option value='" . $year . "' selected>" . $year . " / " . ($year + 1) . "<br/>";
    } else {
      $course_year .= "<option value='" . $year . "'>" . $year . " / " . ($year + 1) . "<br/>";
    }
  }

  $form["general_info_a"] = array(
    '#markup' => '<table class=\'table table-bordered table-hover\'>
    <tr>
      <th colspan="3"><h1>Course Syllabus: ' . $course -> name . '</h1></th>
    </tr>
    <tr>
      <th colspan = "3">A. Information on Subject Placement in Teaching Program Context</th>
    </tr>
    <tr>
      <td> A.1</td>
      <td>Course Code</td>
      <td>' . $course -> code . '</td>
    </tr>
    <tr>
      <td> A.2</td>
      <td>Academic Year</td>
      <td>' . $course -> year . '</td>
    </tr>
    <tr>
      <td> A.3</td>
      <td>Language of Instruction</td>
      <td>' . $course -> lang . '</td>
    </tr>
    <tr>
      <td> A.4</td>
      <td>Program coordinating the course</td>
      <td>' . $departmentx . '</td>
    </tr>
    <tr>
      <td> A.5</td>
      <td>Program that taking the course</td>
      <td>' . $departmentx . '</td>
    </tr>
    <tr>
      <td> A.6</td>
      <td>Study Profile</td>
      <td>' . $course -> degree . '</td>
    </tr>
    <tr>
      <td> A.7</td>
      <td>Mode of Study</td>
      <td>' . $course -> mode . '</td>
    </tr>
    <tr>
      <td> A.8</td>
      <td>Level of Study</td>
      <td>' . $course -> level . '</td>
    </tr>
  </table>'
  );
  $form["general_info_b"] = array(
    '#markup' => '<div class="tabx">
    <input type="hidden" id="knowledgex" name="knowledgex" value="' . (count($course_w_assmeth) - 1) . '">
    <input type="hidden" id="skillx" name="skillx" value="' . (count($course_u_assmeth) - 1) . '">
    <input type="hidden" id="socialx" name="socialx" value="' . (count($course_k_assmeth) - 1) . '">
    <input type="hidden" id="lecturex" name="lecturex" value="' . (count($course_lecture) - 1) . '">
    <input type="hidden" id="labx" name="labx" value="' . (count($course_lab) - 1) . '">
    <input type="hidden" id="discussionx" name="discussionx" value="' . (count($course_discussion) - 1) . '">
    <input type="hidden" id="seminarx" name="seminarx" value="' . (count($course_seminar) - 1) . '">
    <input type="hidden" id="workshopx" name="workshopx" value="' . (count($course_workshop) - 1) . '">
    <input type="hidden" id="elearningx" name="elearningx" value="' . (count($course_elearning) - 1) . '">
    <input type="hidden" id="lec_othersx" name="lec_othersx" value="' . (count($course_lec_other) - 1) . '">

    <script>
      var knowledgex = document.getElementById("knowledgex").value;
      var skillx = document.getElementById("skillx").value;
      var socialx = document.getElementById("socialx").value;
      var lecturex = document.getElementById("lecturex").value;
      var labx = document.getElementById("labx").value;
      var discussionx = document.getElementById("discussionx").value;
      var seminarx = document.getElementById("seminarx").value;
      var workshopx = document.getElementById("workshopx").value;
      var elearningx = document.getElementById("elearningx").value;
      var lec_othersx = document.getElementById("lec_othersx").value;
    </script>
    <table class="table table-bordered table-hover">
      <tr>
        <th colspan="5"><label>B. Course overview (prerequisites, course objectives, learning outcomes, assessment methods, reference to field specific learning outcomes, course content)</label></th>
      </tr>
      <tr>
        <td> B.1</td>
        <td>Prerequisites</td>
        <td colspan="3">
          <select name="prere" id="prere">' . $prere . '</select><br>
          <select name="prere2" id="prere2">' . $prere2 . '</select><br>
          <select name="prere3" id="prere3">' . $prere3 . '</select>
        </td>
      </tr>
      <tr>
        <td> B.2</td>
        <td>Course Objectives</td>
        <td colspan="3"> 
          <select name="objectives[]" id="objectives" multiple>' . $course_objectives . '</select>
        </td>
      </tr>
      <script>
        $(document).ready(function() {

          var last_valid_selection = null;

          $("#objectives").change(function () {
            if($("#objectives option:selected").length > 2) {
              alert("You can only choose 2!");
              $(this).val(last_valid_selection);
            } else {
              last_valid_selection = $(this).val();
            }
          });

        });
      </script>
      <tr>
        <td rowspan="3">B.3</td>
      </tr>
      <tr>
        <td>Code</td>
        <td>Learning Outcomes</td>
        <td>Assessment Methods (eg. midterm/final exam, written/oral exam, test, presentation, term paper)</td>
        <td>Reference to field specific learning outcomes approved by the Senate</td>
      </tr>
      <tr>
        <td colspan="4">
          <div id="tabs">
            <ul>
              <li><a href="#knowledge">Knowledge</a></li>
              <li><a href="#skills">Skills</a></li>
              <li><a href="#social">Social Competences</a></li>
            </ul>
            <div id = "knowledge">
              <div id="add_knowledge"></div>
              <script>
                $(document).ready(function() {
                  $("div#add_knowledge").html("' . $course_knowledge . '");

                  ' . $course_dialog . '
                });

                function dialog1(x) {
                  $("#dialogw" + x).dialog( "open" );
                }
                function close_dialog1(x) {
                  var y = $("#W" + x + "_codex").val();
                  $("#W" + x + "_code").val(y);
                  var w = $("#W" + x + "_codex option:selected").text();
                  var z = w.substr(0, w.indexOf(\'/\'));
                  $("p#labelw_" + x).text(z);
                  $("#dialogw" + x).dialog( "close" );
                }
              </script>
              <script>
                function knowledge() {
                  var knowledgex = $("#knowledgex").val();
                  knowledgex++;
                  $("#knowledgex").val(knowledgex);
                  $("div#add_knowledge").append("<div id=\'dialogw" + knowledgex + "\' title=\'Code Description\'><form><select id=\'W" + knowledgex + "_codex\' name=\'W_codex[]\'>' . $course_code_empty . '</select><input type=\'button\' value=\'Ok\' onclick=\'close_dialog1(" + knowledgex + ");\'></form></div><table class=\'table table-bordered table-hover\'><tr><td>W" + knowledgex + "</td><td><input type=\'hidden\' id=\'W" + knowledgex + "_code\' name=\'W_code[]\'><textarea id=\'W_outcomes[]\' name=\'W_outcomes[]\'></textarea></td><td><select id=\'W" + knowledgex + "_assmeths\' name=\'W" + knowledgex + "_assmeths\'  onchange=\'knowledge_onblur(" + knowledgex + ")\'>' . $course_assmethx . '</select></td><td><form><input type=\'button\' value=\'Code\' onclick=\'dialog1(" + knowledgex + ");\'></form></td><td><p id=\'labelw_" + knowledgex + "\'></p></td></tr></table>");

                  $("#dialogw" + knowledgex).dialog({
                    autoOpen: false,
                    show: {
                      effect: "blind",
                      duration: 500
                    },
                    height:"auto",
                    width:"90%"
                  });
                }

                function dialog1(x) {
                  $("#dialogw" + x).dialog( "open" );
                }
                function close_dialog1(x) {
                  var y = $("#W" + x + "_codex").val();
                  $("#W" + x + "_code").val(y);
                  var w = $("#W" + x + "_codex option:selected").text();
                  var z = w.substr(0, w.indexOf(\'/\'));
                  $("p#labelw_" + x).text(z);
                  $("#dialogw" + x).dialog("close");
                }
              </script>
            </div>
            <div id = "skills">
              <div id="add_skill"></div>
              <script>
                $(document).ready(function() {
                  $("div#add_skill").html("' . $course_skill . '");

                  ' . $course_dialog2 . '
                });

                function dialog2(x) {
                  $("#dialogu" + x).dialog( "open" );
                }
                function close_dialog2(x) {
                  var y = $("#U" + x + "_codex").val();
                  $("#U" + x + "_code").val(y);
                  var w = $("#U" + x + "_codex option:selected").text();
                  var z = w.substr(0, w.indexOf(\'/\'));
                  $("p#labelu_" + x).text(z);
                  $("#dialogu" + x).dialog( "close" );
                }
              </script>
              <script>
                function skill() {
                  var skillx = $("#skillx").val();
                  skillx++;
                  $("#skillx").val(skillx);

                  $("div#add_skill").append("<div id=\'dialogu" + skillx + "\' title=\'Code Description\'><form><select id=\'U" + skillx + "_codex\' name=\'U_codex[]\'>' . $course_code_empty . '</select><input type=\'button\' value=\'Ok\' onclick=\'close_dialog2(" + skillx + ");\'></form></div><table class=\'table table-bordered table-hover\'><tr><td>U" + skillx + "</td><td><input type=\'hidden\' id=\'U" + skillx + "_code\' name=\'U_code[]\'><textarea id=\'U_outcomes[]\' name=\'U_outcomes[]\'></textarea></td><td><select id=\'U" + skillx + "_assmeths\' name=\'U" + skillx + "_assmeths\'  onchange=\'skill_onblur(" + skillx + ")\'>' . $course_assmethx . '</select></td><td><form><input type=\'button\' value=\'Code\' onclick=\'dialog2(" + skillx + ");\'></form></td><td><p id=\'labelu_" + skillx + "\'></p></td></tr></table>");

                  $("#dialogu" + skillx).dialog({
                    autoOpen: false,
                    show: {
                      effect: "blind",
                      duration: 500
                    },
                    height:"auto",
                    width:"90%"
                  });
                }

                function dialog2(x) {
                  $("#dialogu" + x).dialog( "open" );
                }
                function close_dialog2(x) {
                  var y = $("#U" + x + "_codex").val();
                  $("#U" + x + "_code").val(y);
                  var w = $("#U" + x + "_codex option:selected").text();
                  var z = w.substr(0, w.indexOf(\'/\'));
                  $("p#labelu_" + x).text(z);
                  $("#dialogu" + x).dialog( "close" );
                }
              </script>
            </div>
            <div id = "social">
              <div id="add_social"></div>
              <script>
                $(document).ready(function() {
                  $("div#add_social").html("' . $course_social . '");

                  ' . $course_dialog3 . '
                });

                function dialog3(x) {
                  $("#dialogk" + x).dialog( "open" );
                }
                function close_dialog3(x) {
                  var y = $("#K" + x + "_codex").val();
                  $("#K" + x + "_code").val(y);
                  var w = $("#K" + x + "_codex option:selected").text();
                  var z = w.substr(0, w.indexOf(\'/\'));
                  $("p#labelk_" + x).text(z);
                  $("#dialogk" + x).dialog( "close" );
                }
              </script>
              <script>
                function social() {
                  var socialx = $("#socialx").val();
                  socialx++;
                  $("#socialx").val(socialx);

                  $("div#add_social").append("<div id=\'dialogk" + socialx + "\' title=\'Code Description\'><form><select id=\'K" + socialx + "_codex\' name=\'K_codex[]\'>' . $course_code_empty . '</select><input type=\'button\' value=\'Ok\' onclick=\'close_dialog3(" + socialx + ");\'></form></div><table class=\'table table-bordered table-hover\'><tr><td>K" + socialx + "</td><td><input type=\'hidden\' id=\'K" + socialx + "_code\' name=\'K_code[]\'><textarea id=\'K_outcomes[]\' name=\'K_outcomes[]\'></textarea></td><td><select id=\'K" + socialx + "_assmeths\' name=\'K" + socialx + "_assmeths\'  onchange=\'social_onblur(" + socialx + ")\'>' . $course_assmethx . '</select></td><td><form><input type=\'button\' value=\'Code\' onclick=\'dialog3(" + socialx + ");\'></form></td><td><p id=\'labelk_" + socialx + "\'></p></td></tr></table>");

                  $("#dialogk" + socialx).dialog({
                    autoOpen: false,
                    show: {
                      effect: "blind",
                      duration: 500
                    },
                    height:"auto",
                    width:"90%"
                  });
                }

                function dialog3(x) {
                  $("#dialogk" + x).dialog( "open" );
                }
                function close_dialog3(x) {
                  var y = $("#K" + x + "_codex").val();
                  $("#K" + x + "_code").val(y);
                  var w = $("#K" + x + "_codex option:selected").text();
                  var z = w.substr(0, w.indexOf(\'/\'));
                  $("p#labelk_" + x).text(z);
                  $("#dialogk" + x).dialog( "close" );
                }
              </script>
            </div>
          </div>
          <script>
            $(function() {
             $(\'#tabs\').tabs();
           });
         </script>
       </td>
     </tr>
     <!-- B3 -->
     <tr>
      <td>B.4</td>
      <td colspan="4">
        <div id="tabs2">
          <ul>
            <li><a href="#lectures">Lectures</a></li>
            <li><a href="#labs">Labs</a></li>
            <li><a href="#discussions">Discussions</a></li>
            <li><a href="#seminars">Seminars</a></li>
            <li><a href="#workshops">Workshops</a></li>
            <li><a href="#elearnings">E-learnings</a></li>
            <li><a href="#lec_other">Others</a></li>
          </ul>
          <div id = "lectures">
            <div id="add_lectures"></div>
            <script>
              $(document).ready(function() {
                $("div#add_lectures").html("' . $course_lectures . '");
              });
            </script>

            <script>
              function lectures() {
                var lecturex = $("#lecturex").val();
                lecturex++;
                $("#lecturex").val(lecturex);

                $("#add_lectures").append("<table class=\'table table-bordered table-hover\'><tr><td>Topic " + lecturex + ":</td><td><textarea name=\'lecture[]\' id=\'lecture" + (lecturex - 1) + "\' onblur=\'lec_onblur(" + (lecturex - 1) + ")\'></textarea></td><td><input type=\'number\' id=\'ws_hour" + (lecturex - 1) + "\' name=\'ws_hour[]\' onblur=\'lecture_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour2" + (lecturex - 1) + "\' name=\'ws_hour2[]\' onblur=\'lecture_onblur()\'> h</td></tr></table>");}
              </script>
            </div>
            <div id = "labs">
              <div id="add_labs"></div>
              <script>
                $(document).ready(function() {
                  $("div#add_labs").html("' . $course_labs . '");
                });
              </script>
              <script>
                function labs() {
                  var labx = $("#labx").val();
                  labx++;
                  $("#labx").val(labx);

                  $("#add_labs").append("<table class=\'table table-bordered table-hover\'><tr><td>Topic " + labx + ":</td><td><textarea name=\'lab[]\' id=\'lab" + (labx - 1) + "\' onblur=\'lab_onblur(" + (labx - 1) + ")\'></textarea></td><td><input type=\'number\' id=\'ws_hour" + (labx - 1) + "\' name=\'ws_hour[]\' onblur=\'lab_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour2" + (labx - 1) + "\' name=\'ws_hour2[]\' onblur=\'lab_onblur()\'> h</td></tr></table>");}
                </script>
              </div>
              <div id = "discussions">
                <div id="add_discussion"></div>
                <script>
                  $(document).ready(function() {
                    $("div#add_discussion").html("' . $course_discussions . '");
                  });
                </script>
                <script>
                  function discussions() {
                    var discussionx = $("#discussionx").val();
                    discussionx++;
                    $("#discussionx").val(discussionx);

                    $("#add_discussion").append("<table class=\'table table-bordered table-hover\'><tr><td>Topic " + discussionx + ":</td><td><textarea name=\'discussion[]\' id=\'discussion" + (discussionx - 1) + "\' onblur=\'discussion_onblur(" + (discussionx - 1) + ")\'></textarea></td><td><input type=\'number\' id=\'ws_hour" + (discussionx - 1) + "\' name=\'ws_hour[]\' onblur=\'discussion_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour2" + (discussionx - 1) + "\' name=\'ws_hour2[]\' onblur=\'discussion_onblur()\'> h</td></tr></table>");}
                  </script>
                </div>
                <div id = "seminars">
                  <div id="add_seminars"></div>
                  <script>
                    $(document).ready(function() {
                      $("div#add_seminars").html("' . $course_seminars . '");
                    });
                  </script>
                  <script>
                    function seminars() {
                      var seminarx = $("#seminarx").val();
                      seminarx++;
                      $("#seminarx").val(seminarx);

                      $("#add_seminars").append("<table class=\'table table-bordered table-hover\'><tr><td>Topic " + seminarx + ":</td><td><textarea name=\'seminar[]\' id=\'seminar" + (seminarx - 1) + "\' onblur=\'seminar_onblur(" + (seminarx - 1) + ")\'></textarea></td><td><input type=\'number\' id=\'ws_hour" + (seminarx - 1) + "\' name=\'ws_hour[]\' onblur=\'seminar_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour2" + (seminarx - 1) + "\' name=\'ws_hour2[]\' onblur=\'seminar_onblur()\'> h</td></tr></table>");}
                    </script>
                  </div>
                  <div id = "workshops">
                    <div id="add_workshops"></div>
                    <script>
                      $(document).ready(function() {
                        $("div#add_workshops").html("' . $course_workshops . '");
                      });
                    </script>
                    <script>
                      function workshops() {
                        var workshopx = $("#workshopx").val();
                        workshopx++;
                        $("#workshopx").val(workshopx);

                        $("#add_workshops").append("<table class=\'table table-bordered table-hover\'><tr><td>Topic " + workshopx + ":</td><td><textarea name=\'workshop[]\' id=\'workshop" + (workshopx - 1) + "\' onblur=\'workshop_onblur(" + (workshopx - 1) + ")\'></textarea></td><td><input type=\'number\' id=\'ws_hour" + (workshopx - 1) + "\' name=\'ws_hour[]\' onblur=\'workshop_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour2" + (workshopx - 1) + "\' name=\'ws_hour2[]\' onblur=\'workshop_onblur()\'> h</td></tr></table>");}
                      </script>
                    </div>
                    <div id = "elearnings">
                      <div id="add_elearnings"></div>
                      <script>
                        $(document).ready(function() {
                          $("div#add_elearnings").html("' . $course_elearnings . '");
                        });
                      </script>
                      <script>
                        function elearnings() {
                          var elearningx = $("#elearningx").val();
                          elearningx++;
                          $("#elearningx").val(elearningx);

                          $("#add_elearnings").append("<table class=\'table table-bordered table-hover\'><tr><td>Topic " + elearningx + ":</td><td><textarea name=\'elearning[]\' id=\'elearning" + (elearningx - 1) + "\' onblur=\'elearning_onblur(" + (elearningx - 1) + ")\'></textarea></td><td><input type=\'number\' id=\'ws_hour" + (elearningx - 1) + "\' name=\'ws_hour[]\' onblur=\'elearning_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour2" + (elearningx - 1) + "\' name=\'ws_hour2[]\' onblur=\'elearning_onblur()\'> h</td></tr></table>");
                        }
                      </script>
                    </div>
                    <div id="lec_other">
                      <div id="add_lec_others"></div>
                      <script>
                        $(document).ready(function() {
                          $("div#add_lec_others").html("' . $course_lec_others . '");
                        });
                      </script>
                      <script>
                        function lec_others() {
                          var lec_othersx = $("#lec_othersx").val();
                          lec_othersx++;
                          $("#lec_othersx").val(lec_othersx);

                          $("#add_lec_others").append("<table class=\'table table-bordered table-hover\'><tr><td>Topic " + lec_othersx + ":</td><td><textarea name=\'lec_other[]\' id=\'lec_other" + (lec_othersx - 1) + "\' onblur=\'lec_other_onblur(" + (lec_othersx - 1) + ")\'></textarea></td><td><input type=\'number\' id=\'ws_hour" + (lec_othersx - 1) + "\' name=\'ws_hour[]\' onblur=\'other_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour2" + (lec_othersx - 1) + "\' name=\'ws_hour2[]\' onblur=\'other_onblur()\'> h</td></tr></table>");
                        }
                      </script>
                    </div>
                    <script>
                      $(function() {
                       $( \'#tabs2\' ).tabs();
                     });
                   </script>
                 </td>
               </tr>
             </div>

             <tr>
              <td>B.5</td>
              <td>Criteria for receiving credit for the course (assessment methods)</td>
              <td colspan="3">Following percentages of marks meaning<br>*&#09;0-49 -> 2 ----- Fail<br>*&#09;50-59 -> 3 ---- Satisfactory<br>*&#09;60-69 -> 3,5 -- Satisfactory Plus<br>*&#09;70-79 -> 4 ---- Good<br>*&#09;80-89 -> 4,5 -- Good Plus<br>*&#09;90-100 -> 5 --- Very Good<br></td>
            </tr>
            <tr>
              <td></td>
              <td colspan="2">Assessment Method</td>
              <td colspan="2">Percentage</td>
            </tr>
          </table>

          <div id="add_assmethw"></div>
          <script>
            $(document).ready(function() {
              $("#add_assmethw").append("' . $course_assmeths . '");
            });

            function knowledge_onblur(y) {
              var x = "w" + y;
              var name = $("#W" + y + "_assmeths option:selected").text();

              if($("#" + x).length == 0) {
                $("#add_assmethw").append("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
              } else {
                $("#" + x).html("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
              }
            }

            function skill_onblur(y) {
              var x = "u" + y;
              var name = $("#U" + y + "_assmeths option:selected").text();

              if($("#" + x).length == 0) {
                $("#add_assmethw").append("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
              } else {
                $("#" + x).html("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
              }
            }

            function social_onblur(y) {
              var x = "k" + y;
              var name = $("#K" + y + "_assmeths option:selected").text();

              if($("#" + x).length == 0) {
                $("#add_assmethw").append("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
              } else {
                $("#" + x).html("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'number\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
              }
            }
          </script>');
$form["general_info_c"] = array(
  '#markup' => '
  <script>
    $(document).ready(function() {
      $("#add_others").html("<input type=\'hidden\' id=\'others\' value=\'' . (count($course_other) + 1) . '\'><input type=\'hidden\' id=\'workloads\' value=\'' . (count($course_ws_hour) - 1) . '\'><input type=\'hidden\' id=\'workloads2\' value=\'' . (count($course_ws_hour2) - 1) . '\'><table class=\'table table-bordered table-hover\'><tbody><tr><th colspan = \'4\'>C. Readings</th></tr><tr><td>C.1</td><td>Compulsory readings</td><td colspan = \'2\'><textarea id=\'compulsory\' name=\'compulsory\' style=\'height: 70px; width: 250px;\'>' . $course -> compulsory . '</textarea></td></tr><tr><td>C.2</td><td>Supplementary readings</td><td><textarea id=\'supplementary\' name=\'supplementary\' style=\'height: 70px; width: 250px;\'>' . $course -> supplementary . '</textarea></td><td><form><input type=\'button\' onclick=\'otherw()\' value=\'Add more\'></form></td></tr></tbody></table>' . $course_readings . '");
    });
    function otherw() {
      var others = $("#others").val();
      others++;
      $("#others").val(others);

      $("#add_others").append("<table class=\'table table-bordered table-hover\'><tbody><tr><td>C." + others + "</td><td><input type=\'text\' id=\'other_name[]\' name=\'other_name[]\'></td><td><textarea id=\'other[]\' name=\'other[]\' style=\'height: 70px; width: 250px;\'></textarea></td><td></td><td></td><td></td><td></td></tr></tbody></table>");
    }
  </script>
  <div id="add_others"></div>');
$form["general_info_d"] = array(
  '#markup' => '
          <script>
          $(document).ready(function() {
            $("#add_workload").html("<table class=\'table table-bordered table-hover\'><tbody><tr><th colspan = \'5\'>D. Student workload</th></tr><tr><td>D.1</td><td colspan=\'3\'>ECTS Credits</td><td>' . $course -> ects . '</td></tr><tr><td>D.2</td><td colspan=\'3\'>Workload (estimated number of hours )</td><td>' . ($course -> ects * 25) . '</td></tr></tbody></table>");
            });

            function other_onblur() {
              var x = 0;
              for (i = 0; i < $("#lec_othersx").val(); i++) {
                x += parseInt($("#ws_hour_other" + i).val(), 10);
              }
              for (i = 0; i < $("#lec_othersx").val(); i++) {
                x += parseInt($("#ws_hour_other2" + i).val(), 10);
              }
              $("div#left_hours_other").html((parseInt(' . ($course -> ects * 25) . ', 10) - x) + " hours left");
            }

            function lecture_onblur() {
              var x = 0;
              for (i = 0; i < $("#lecturex").val(); i++) {
                x += parseInt($("#ws_hour_lecture" + i).val(), 10);
              }
              for (i = 0; i < $("#lecturex").val(); i++) {
                x += parseInt($("#ws_hour_lecture2" + i).val(), 10);
              }
              $("div#left_hours_lecture").html((parseInt(' . ($course -> ects * 25) . ', 10) - x) + " hours left");
            }

            function lab_onblur() {
              var x = 0;
              for (i = 0; i < $("#labx").val(); i++) {
                x += parseInt($("#ws_hour_lab" + i).val(), 10);
              }
              for (i = 0; i < $("#labx").val(); i++) {
                x += parseInt($("#ws_hour_lab2" + i).val(), 10);
              }
              $("div#left_hours_lab").html((parseInt(' . ($course -> ects * 25) . ', 10) - x) + " hours left");
            }

            function discussion_onblur() {
              var x = 0;
              for (i = 0; i < $("#discussionx").val(); i++) {
                x += parseInt($("#ws_hour_discussion" + i).val(), 10);
              }
              for (i = 0; i < $("#discussionx").val(); i++) {
                x += parseInt($("#ws_hour_discussion2" + i).val(), 10);
              }
              $("div#left_hours_discussion").html((parseInt(' . ($course -> ects * 25) . ', 10) - x) + " hours left");
            }

            function seminar_onblur() {
              var x = 0;
              for (i = 0; i < $("#seminarx").val(); i++) {
                x += parseInt($("#ws_hour_seminar" + i).val(), 10);
              }
              for (i = 0; i < $("#seminarx").val(); i++) {
                x += parseInt($("#ws_hour_seminar2" + i).val(), 10);
              }
              $("div#left_hours_seminar").html((parseInt(' . ($course -> ects * 25) . ', 10) - x) + " hours left");
            }

            function workshop_onblur() {
              var x = 0;
              for (i = 0; i < $("#workshopx").val(); i++) {
                x += parseInt($("#ws_hour_workshop" + i).val(), 10);
              }
              for (i = 0; i < $("#workshopx").val(); i++) {
                x += parseInt($("#ws_hour_workshop2" + i).val(), 10);
              }
              $("div#left_hours_workshop").html((parseInt(' . ($course -> ects * 25) . ', 10) - x) + " hours left");
            }

            function elearning_onblur() {
              var x = 0;
              for (i = 0; i < $("#elearningx").val(); i++) {
                x += parseInt($("#ws_hour_elearning" + i).val(), 10);
              }
              for (i = 0; i < $("#elearningx").val(); i++) {
                x += parseInt($("#ws_hour_elearning2" + i).val(), 10);
              }
              $("div#left_hours_elearning").html((parseInt(' . ($course -> ects * 25) . ', 10) - x) + " hours left");
            }

          // function workloadw() {
          //   var workloads = $("#workloads").val();
          //   workloads++;
          //   $("#workloads").val(workloads);

          //   var workloads2 = $("#workloads2").val();
          //   workloads2++;
          //   $("#workloads2").val(workloads2);

          //   $("#add_workload").append("<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td><input type=\'text\' name=\'ws_activity[]\'></td><td><input type=\'text\' id=\'ws_hour" + (workloads - 1) + "\' name=\'ws_hour[]\' onblur=\'workload_onblur()\'> h</td><td><input type=\'text\' id=\'ws_hour2" + (workloads2 - 1) + "\' name=\'ws_hour2[]\' onblur=\'workload_onblur()\'> h</td></tr></tbody></table>");
          // }

          // function workload_onblur() {
          //   var x = 0;
          //   for (i = 0; i < $("#workloads").val(); i++) {
          //     x += parseInt($("#ws_hour" + i).val(), 10);
          //   }
          //   for (i = 0; i < $("#workloads2").val(); i++) {
          //     x += parseInt($("#ws_hour2" + i).val(), 10);
          //   }
          //   $("div#left_hours").html((parseInt(' . ($course -> ects * 25) . ', 10) - x) + " hours left");
          // }
  </script>
    <div id="add_workload"></div>
');
$form["general_info_e"] = array(
  '#markup' => '<table class=\'table table-bordered table-hover\'>
  <tr>
    <th colspan="3">E. Course coordinator, teacher(s), date of syllabus preparation</th>
  </tr>
  <tr>
    <td>E.1</td>
    <td> Course Coordinator</td>
    <td>' . $coordinatorx . '</td>
  </tr>
  <tr>
    <td>E.2</td>
    <td> Academic Teacher</td>
    <td>' . $teachers . '</td>
  </tr>
  <tr>
    <td>E.3</td>
    <td>Date of Preparation(latest submission date)</td>
    <td>' . $course -> pre_date . '</td>
  </tr>
</table>'
);
$form["general_info_f"] = array(
  '#markup' => '<table class=\'table table-bordered table-hover\'>
  <tr><th>Note from Head of Program:</th></tr>
  <tr>
    <td>' . $course_note . '</td>
  </tr>
</table>');

$form['submit_save'] = array(
  '#type' => 'submit',
  '#value' => t('Save'),
  '#submit' => array('staff_course_submit_save'),
  );
$form['submit_cancel'] = array(
  '#type' => 'submit',
  '#value' => t('Cancel'),
  '#submit' => array('staff_course_submit_cancel'),
  );
$form['submit_send'] = array(
 '#type' => 'submit',
 '#value' => t('Send'),
 '#submit' => array('staff_course_submit_send'),
 );

return $form;
}

function staff_course_submit_save(){
	$idx = filter_input(INPUT_GET, 'idx');

  $course_name = htmlspecialchars($_POST['course_name']);

// A
  $course_code = htmlspecialchars($_POST['course_code']);
  $year = htmlspecialchars($_POST['year']);
  $language = htmlspecialchars($_POST['language']);
  $coor_department = htmlspecialchars($_POST['coor_department']);
  $study = htmlspecialchars($_POST['study']);
  $profile = htmlspecialchars($_POST['profile']);
  $mode = htmlspecialchars($_POST['mode']);
  $level = htmlspecialchars($_POST['level']);
  // drupal_set_message("code: ".$course_code."\nyear ".$year."\nlang ".$language."\ncoor dep ".$coor_department."\nstudy ".$study."\nprof ".$profile."\nmode ".$mode."\nlevel ".$level."\nmeth ".$method."\nhour ".$hour);

// B
  $prere = htmlspecialchars($_POST['prere']);
  $prere2 = htmlspecialchars($_POST['prere2']);
  $prere3 = htmlspecialchars($_POST['prere3']);
  $objective = "";
  if (isset($_POST['objectives'])) {
    foreach ($_POST['objectives'] as $objectives) {
      $objective .= htmlspecialchars($objectives) . ";";
    }
  }
  $W_outcomes = "";
  foreach ($_POST['W_outcomes'] as $Woutcome) {
    $W_outcomes .= htmlspecialchars($Woutcome) . ";";
  }
  $W_assmeths = "";
  for ($i=1; $i <= $_POST['knowledgex']; $i++) {
    $W_assmeths .= htmlspecialchars($_POST['W' . $i . '_assmeths']) . ";";
  }
  $W_codes = "";
  if (isset($_POST['W_code'])) {
    foreach ($_POST['W_code'] as $Wcode) {
      $W_codes .= htmlspecialchars($Wcode) . ";";
    }
  }

  $U_outcomes = "";
  foreach ($_POST['U_outcomes'] as $Uoutcome) {
    $U_outcomes .= htmlspecialchars($Uoutcome) . ";";
  }
  $U_assmeths = "";
  for ($i=1; $i <= $_POST['skillx']; $i++) { 
    $U_assmeths .= htmlspecialchars($_POST['U' . $i . '_assmeths']) . ";";
  }
  $U_codes = "";
  if (isset($_POST['U_code'])) {
    foreach ($_POST['U_code'] as $Ucode) {
      $U_codes .= htmlspecialchars($Ucode) . ";";
    }
  }

  $K_outcomes = "";
  foreach ($_POST['K_outcomes'] as $Koutcome) {
    $K_outcomes .= htmlspecialchars($Koutcome) . ";";
  }
  $K_assmeths = "";
  for ($i=1; $i <= $_POST['socialx']; $i++) { 
    $K_assmeths .= htmlspecialchars($_POST['K' . $i . '_assmeths']) . ";";
  }
  $K_codes = "";
  if (isset($_POST['K_code'])) {
    foreach ($_POST['K_code'] as $Kcode) {
      $K_codes .= htmlspecialchars($Kcode) . ";";
    }
  }

  $lecture = "";
  foreach ($_POST['lecture'] as $lectures) {
    $lecture .= htmlspecialchars($lectures) . ";";
  }
  $lab = "";
  foreach ($_POST['lab'] as $labs) {
    $lab .= htmlspecialchars($labs) . ";";
  }
  $discussion = "";
  foreach ($_POST['discussion'] as $discussions) {
    $discussion .= htmlspecialchars($discussions) . ";";
  }
  $seminar = "";
  foreach ($_POST['seminar'] as $seminars) {
    $seminar .= htmlspecialchars($seminars) . ";";
  }
  $workshop = "";
  foreach ($_POST['workshop'] as $workshops) {
    $workshop .= htmlspecialchars($workshops) . ";";
  }
  $elearning = "";
  foreach ($_POST['elearning'] as $elearnings) {
    $elearning .= htmlspecialchars($elearnings) . ";";
  }
  $lec_other = "";
  foreach ($_POST['lec_other'] as $lec_others) {
    $lec_other .= htmlspecialchars($lec_others) . ";";
  }

  $percent = "";
  if (isset($_POST['percent'])) {
   foreach ($_POST['percent'] as $percents) {
     $percent .= htmlspecialchars($percents) . ";";
   }
 }

// C
 $compulsory = htmlspecialchars($_POST['compulsory']);
 $supplementary = htmlspecialchars($_POST['supplementary']);
 $other_name = "";
 if (isset($_POST['other_name'])) {
  foreach ($_POST['other_name'] as $other_names) {
    $other_name .= htmlspecialchars($other_names) . ";";
  }
}
$other = "";
if (isset($_POST['other'])) {
  foreach ($_POST['other'] as $others) {
    $other .= htmlspecialchars($others) . ";";
  }
}

// D
  //$ects = htmlspecialchars($_POST['ects']);
$ws_hour = "";
if (isset($_POST['ws_hour'])) {
  foreach ($_POST['ws_hour'] as $ws_hours) {
   $ws_hour .= htmlspecialchars($ws_hours) . ";";
 }
}
$ws_activity = "";
if (isset($_POST['ws_activity'])) {
  foreach ($_POST['ws_activity'] as $ws_activities) {
    $ws_activity .= htmlspecialchars($ws_activities) . ";";
  }
}

$ws_hour2 = "";
if (isset($_POST['ws_hour2'])) {
  foreach ($_POST['ws_hour2'] as $ws_hours2) {
   $ws_hour2 .= htmlspecialchars($ws_hours2) . ";";
 }
}

// E
$course_coordinator = htmlspecialchars($_POST['course_coordinator']);
$course_teacher = "";
if (isset($_POST['course_teacher'])) {
      $course_teacher .= htmlspecialchars($_POST['course_teacher']) . ";";
  } else {
    $course_teacher .= "0;";
  }
  if (isset($_POST['course_teacher2'])) {
      $course_teacher .= htmlspecialchars($_POST['course_teacher2']) . ";";
  } else {
    $course_teacher .= "0;";
  }
  if (isset($_POST['course_teacher3'])) {
      $course_teacher .= htmlspecialchars($_POST['course_teacher3']) . ";";
  } else {
    $course_teacher .= "0;";
  }
$pre_date = htmlspecialchars($_POST['pre_date']);

  // drupal_set_message($course_teacher);

// if (db_query("UPDATE {syllabus_main_course} SET {name}='" . $course_name . "', {code}='" . $course_code . "', {year}='" . $year . "', {lang}='" . $language . "', {dep}='" . $coor_department . "', {field}='" . $study . "', {degree}='" . $profile . "', {mode}='" . $mode . "', {level}='" . $level . "', {prere}='" . $prere . "', {prere2}='" . $prere2 . "', {prere3}='" . $prere3 . "', {objective}='" . $objective . "', {w_outcome}='" . $W_outcomes . "', {w_assmeth}='" . $W_assmeths . "', {w_code}='" . $W_codes . "', {u_outcome}='" . $U_outcomes . "', {u_assmeth}='" . $U_assmeths . "', {u_code}='" . $U_codes . "', {k_outcome}='" . $K_outcomes . "', {k_assmeth}='" . $K_assmeths . "', {k_code}='" . $K_codes . "', {lecture}='" . $lecture . "', {lab}='" . $lab . "', {discussion}='" . $discussion . "', {seminar}='" . $seminar . "', {workshop}='" . $workshop . "', {elearning}='" . $elearning . "', {lec_other}='" . $lec_other . "', {percent}='" . $percent . "', {compulsory}='" . $compulsory . "', {supplementary}='" . $supplementary . "', {other_name}='" . $other_name . "', {other}='" . $other . "', {ws_hour}='" . $ws_hour . "', {ws_activity}='" . $ws_activity . "', {ws_non_con_hour}='" . $ws_hour2 . "', {coordinator}='" . $course_coordinator . "', {teacher}='" . $course_teacher . "', {pre_date}='" . $pre_date . "' WHERE {id}=" . $idx)) {
if (db_query("UPDATE {syllabus_main_course} SET {prere}='" . $prere . "', {prere2}='" . $prere2 . "', {prere3}='" . $prere3 . "', {objective}='" . $objective . "', {w_outcome}='" . $W_outcomes . "', {w_assmeth}='" . $W_assmeths . "', {w_code}='" . $W_codes . "', {u_outcome}='" . $U_outcomes . "', {u_assmeth}='" . $U_assmeths . "', {u_code}='" . $U_codes . "', {k_outcome}='" . $K_outcomes . "', {k_assmeth}='" . $K_assmeths . "', {k_code}='" . $K_codes . "', {lecture}='" . $lecture . "', {lab}='" . $lab . "', {discussion}='" . $discussion . "', {seminar}='" . $seminar . "', {workshop}='" . $workshop . "', {elearning}='" . $elearning . "', {lec_other}='" . $lec_other . "', {percent}='" . $percent . "', {compulsory}='" . $compulsory . "', {supplementary}='" . $supplementary . "', {other_name}='" . $other_name . "', {other}='" . $other . "' WHERE {id}=" . $idx)) {
    // $course_teacher = $_POST['course_teacher'];
  drupal_set_message('Course succesfully saved!');
    // drupal_goto('syllabus_main/staff_staff');
} else {
  drupal_set_message('Some Problem!');
}
}

function staff_course_submit_cancel(){
	drupal_goto('syllabus_main/staff_staff');
}

function staff_course_submit_send() {
  $idx = filter_input(INPUT_GET, 'idx');
    if (db_query("UPDATE {syllabus_main_course} SET {status}=1 WHERE {id}=" . $idx)) {
     drupal_set_message('Sent!');
   }
}