<?php

//HoD new course

function new_course_page() {
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

  global $user;
  $idx = filter_input(INPUT_GET, 'idx');
  $course = db_query("SELECT * FROM {syllabus_main_course} WHERE {id}='" . $idx . "' LIMIT 1") -> fetchObject();
  $results = db_query("SELECT * FROM {syllabus_main_course}");
  $departmentwww = db_query("SELECT {id} FROM {syllabus_main_department} WHERE {hod}='" . $user -> uid . "' LIMIT 1") -> fetchField();
  $preres = db_query("SELECT * FROM {syllabus_main_prerequisites} WHERE {dep}='" . $departmentwww . "'");
  $departments = db_query("SELECT * FROM {syllabus_main_department}");
  $codes = db_query("SELECT * FROM {syllabus_main_code_desc} WHERE {dep}='" . $departmentwww . "'");
  $objectives = db_query("SELECT * FROM {syllabus_main_objective} WHERE {dep}='" . $departmentwww . "'");
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

  $course_w_code_x = "";
  $course_u_code_x = "";
  $course_k_code_x = "";
  $course_code_empty = "";

  foreach ($codes as $code) {
      $course_code_empty .= "<option value='" . $code -> id . "'>" . $code -> code . " / " . $code -> description . "<br/>";
  }

  $course_w_assmeth_xx = "";
  $course_u_assmeth_xx = "";
  $course_k_assmeth_xx = "";
  foreach ($assmeths as $assmeth) {
        $course_w_assmeth_xx .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";

        $course_u_assmeth_xx .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";

        $course_k_assmeth_xx .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";
  }

// knowledge
  $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");

  $course_knowledge = "<div id='dialogw1' title='Code Description'><form><select id='W1_codex' name='W_codex[]'>" . $course_code_empty . "</select><input type='button' value='Ok' onclick='close_dialog1(1);'></form></div><table class=\'table table-bordered table-hover\'><tr><td>W1</td><td><input type=\'hidden\' id=\'W1_code\' name=\'W_code[]\'><textarea id=\'W_outcomes[]\' name=\'W_outcomes[]\'></textarea></td><td><select id=\'W1_assmeths\' name=\'W1_assmeths\' onchange=\'knowledge_onblur(1)\'>" . $course_w_assmeth_xx . "</select></td><td><form><input type='button' onclick='dialog1(1);' value='Code'></form></td><td><p id=\'labelw_1\'></p></td><td><form><input type='button' onclick='knowledge()' value='Add more'></form></td></tr></table>";

// skill
  $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");

  $course_skill = "<div id='dialogu1' title='Code Description'><form><select id='U1_codex' name='U_codex[]'>" . $course_code_empty . "</select><input type='button' value='Ok' onclick='close_dialog2(1);'></form></div><table class=\'table table-bordered table-hover\'><tr><td>U1</td><td><input type=\'hidden\' id=\'U1_code\' name=\'U_code[]\'><textarea id=\'U_outcomes[]\' name=\'U_outcomes[]\'></textarea></td><td><select id=\'U1_assmeths\' name=\'U1_assmeths\' onchange=\'skill_onblur(1)\'>" . $course_u_assmeth_xx . "</select></td><td><form><input type='button' onclick='dialog2(1);' value='Code'></form></td><td><p id=\'labelu_1\'></p></td><td><form><input type=\'button\' onclick=\'skill()\' value=\'Add more\'></form></td></tr></table>";

// social
  $codes = db_query("SELECT * FROM {syllabus_main_code_desc}");

  $course_social = "<div id='dialogk1' title='Code Description'><form><select id='K1_codex' name='K_codex[]'>" . $course_code_empty . "</select><input type='button' value='Ok' onclick='close_dialog3(1);'></form></div><table class=\'table table-bordered table-hover\'><tr><td>K1</td><td><input type=\'hidden\' id=\'K1_code\' name=\'K_code[]\'><textarea id=\'K_outcomes[]\' name=\'K_outcomes[]\'></textarea></td><td><select id=\'K1_assmeths\' name=\'K1_assmeths\' onchange=\'social_onblur(1)\'>" . $course_k_assmeth_xx . "</select></td><td><form><input type='button' onclick='dialog3(1);' value='Code'></form></td><td><p id=\'labelk_1\'></p></td><td><form><input type=\'button\' onclick=\'social(1)\' value=\'Add more\'></form></td></tr></table>";


// lecture
  $course_lectures = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_lecture\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'lecture[]\' id=\'lecture0\' onblur=\'lec_onblur(0)\'></textarea></td><td><input type=\'number\' id=\'ws_hour_lecture0\' name=\'ws_hour[]\' onblur=\'lecture_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour_lecture20\' name=\'ws_hour2[]\' onblur=\'lecture_onblur()\'> h</td><td><form><input type=\'button\' onclick=\'lectures()\' value=\'Add more\'></form></td></tr></table>";

// lab
  $course_labs = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_lab\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'lab[]\' id=\'lab0\' onblur=\'lab_onblur(0)\'></textarea></td><td><input type=\'number\' id=\'ws_hour_lab0\' name=\'ws_hour[]\' onblur=\'lab_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour_lab20\' name=\'ws_hour2[]\' onblur=\'lab_onblur()\'> h</td><td><form><input type=\'button\' onclick=\'labs()\' value=\'Add more\'></form></td></tr></table>";

// discussion
  $course_discussions = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_discussion\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'discussion[]\' id=\'discussion0\' onblur=\'discussion_onblur(0)\'></textarea></td><td><input type=\'number\' id=\'ws_hour_discussion0\' name=\'ws_hour[]\' onblur=\'discussion_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour_discussion20\' name=\'ws_hour2[]\' onblur=\'discussion_onblur()\'> h</td><td><form><input type=\'button\' onclick=\'discussions()\' value=\'Add more\'></form></td></tr></table>";

// seminar
  $course_seminars = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_seminar\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'seminar[]\' id=\'seminar0\' onblur=\'seminar_onblur(0)\'></textarea></td><td><input type=\'number\' id=\'ws_hour_seminar0\' name=\'ws_hour[]\' onblur=\'seminar_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour_seminar20\' name=\'ws_hour2[]\' onblur=\'seminar_onblur()\'> h</td><td><form><input type=\'button\' onclick=\'seminars()\' value=\'Add more\'></form></td></tr></table>";

// workshop
  $course_workshops = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_workshop\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'workshop[]\' id=\'workshop0\' onblur=\'workshop_onblur(0)\'></textarea></td><td><input type=\'number\' id=\'ws_hour_workshop0\' name=\'ws_hour[]\' onblur=\'workshop_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour_workshop20\' name=\'ws_hour2[]\' onblur=\'workshop_onblur()\'> h</td><td><form><input type=\'button\' onclick=\'workshops()\' value=\'Add more\'></form></td></tr></table>";

// elearning
  $course_elearnings = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_elearning\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'elearning[]\' id=\'elearning0\' onblur=\'elearning_onblur(0)\'></textarea></td><td><input type=\'number\' id=\'ws_hour_elearning0\' name=\'ws_hour[]\' onblur=\'elearning_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour_elearning20\' name=\'ws_hour2[]\' onblur=\'elearning_onblur()\'> h</td><td><form><input type=\'button\' onclick=\'elearnings()\' value=\'Add more\'></form></td></tr></table>";

// lec_other
  $course_lec_others = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td>Type of Activity</td><td>Contact Hours</td><td>Non-Contact Hours</td><td><div id=\'left_hours_other\'></div></td></tr></tbody></table><table class=\'table table-bordered table-hover\'><tr><td>Topic 1:</td><td><textarea name=\'lec_other[]\' id=\'lec_other0\' onblur=\'lec_other_onblur(0)\'></textarea></td><td><input type=\'number\' id=\'ws_hour_other0\' name=\'ws_hour[]\' onblur=\'other_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour_other20\' name=\'ws_hour2[]\' onblur=\'other_onblur()\'> h</td><td><form><input type=\'button\' onclick=\'lec_others()\' value=\'Add more\'></form></td></tr></table>";

// workload structure
  // $course_workloads = "<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td><input type=\'text\' name=\'ws_activity[]\'></td><td><input type=\'number\' id=\'ws_hour0\' name=\'ws_hour[]\'> h</td><td><input type=\'number\' id=\'ws_hour20\' name=\'ws_hour2[]\'> h</td><td><form><input type=\'button\' onclick=\'workloadw()\' value=\'Add more\'></form></td></tr></tbody></table>";

  $assmeths = db_query("SELECT * FROM {syllabus_main_assmeth}");

  foreach ($assmeths as $assmeth) {
    $course_assmethx .= "<option value='" . $assmeth -> id . "'>" . $assmeth -> name . "<br/>";
  }

  if (!empty($course -> note)) {
    $course_note = $course -> note;
  } else {
    $course_note = "No new note from Head of Department.";
  }

  foreach ($objectives as $objective) {
      $course_objectives .= "<option value='" . $objective -> id . "'>" . $objective -> name . "<br/>";
  }

  foreach ($profiles as $profile) {
      $course_profile .= "<option value='" . $profile . "'>" . $profile . "<br/>";
  }
  foreach ($modes as $mode) {
      $course_mode .= "<option value='" . $mode . "'>" . $mode . "<br/>";
  }
  foreach ($levels as $level) {
      $course_level .= "<option value='" . $level . "'>" . $level . "<br/>";
  }
  foreach ($languages as $language) {
      $course_lang .= "<option value='" . $language . "'>" . $language . "<br/>";
  }
  foreach ($departments as $department) {
      // $course_dep .= "<option value='" . $department -> id . "'>" . $department -> department_name . "<br/>";
      $course_dep_2 .= "<option value='" . $department -> id . "'>" . $department -> department_name . "<br/>";
  }
  foreach ($users as $userx) {
      $course_teacher .= "<option value='" . $userx -> uid . "'>" . $userx -> name . " / " . $userx -> mail . "<br/>";
      $course_teacher2 .= "<option value='" . $userx -> uid . "'>" . $userx -> name . " / " . $userx -> mail . "<br/>";
      $course_teacher3 .= "<option value='" . $userx -> uid . "'>" . $userx -> name . " / " . $userx -> mail . "<br/>";
      $course_coordinator .= "<option value='" . $userx -> uid . "'>" . $userx -> name . "<br/>";
  }
  foreach ($results as $result) {
      if (!empty($result -> code)) {
        $course_code .= "<option value='" . $result -> code . "'>" . $result -> code . "<br/>";
      } else {
        $course_code .= "<option value=''><br/>";
      }
  }
  foreach ($preres as $prerex) {
      $prere .= "<option value='" . $prerex -> id . "'>" . $prerex -> name . "<br/>";
      $prere2 .= "<option value='" . $prerex -> id . "'>" . $prerex -> name . "<br/>";
      $prere3 .= "<option value='" . $prerex -> id . "'>" . $prerex -> name . "<br/>";
  }
  foreach ($years as $year) {
      $course_year .= "<option value='" . $year . "'>" . $year . " / " . ($year + 1) . "<br/>";
  }

  $form["general_info_a"] = array(
  '#markup' => '<table class=\'table table-bordered table-hover\'>
    <tr>
      <th colspan="5"><h1>Course Syllabus: <input type="text" name="course_name" id="course_name"></h1></th>
    </tr>
    <tr>
      <th colspan = "5">A. Information on Subject Placement in Teaching Program Context</th>
    </tr>
    <tr>
      <td> A.1</td>
      <td colspan="2">Course Code</td>
      <td colspan="2">
            <select name="course_code" id="course_code">' . $course_code . '</select>
        </td>
    </tr>
    <tr>
      <td> A.2</td>
      <td colspan="2">Academic Year</td>
      <td colspan="2">
            <select name="year" id="year">' . $course_year . '</select>
        </td>
    </tr>
    <tr>
      <td> A.3</td>
      <td colspan="2">Language of Instruction</td>
      <td colspan="2">
      <select name="language" id="language">' . $course_lang . '</select></td>
    </tr>
    <tr>
      <td> A.4</td>
      <td colspan="2">Program that taking the course</td>
      <td colspan="2"><select name="study" id="study">' . $course_dep_2 . '</select></td>
    </tr>
    <tr>
      <td> A.5</td>
      <td colspan="2">Degree Profile</td>
      <td colspan="2">
      <select name="profile" id="profile">' . $course_profile . '</select></td>
    </tr>
    <tr>
      <td> A.6</td>
      <td colspan="2">Mode of Study</td>
      <td colspan="2">
      <select name="mode" id="mode">' . $course_mode . '</select></td>
    </tr>
    <tr>
      <td> A.7</td>
      <td colspan="2">Level of Study</td>
      <td colspan="2">
      <select name="level" id="level">' . $course_level . '</select></td>
    </tr>
  </table>');
  $form["general_info_b"] = array(
  '#markup' => '<div class="tabx">
<input type="hidden" id="knowledgex" name="knowledgex" value="1">
<input type="hidden" id="skillx" name="skillx" value="1">
<input type="hidden" id="socialx" name="socialx" value="1">
<input type="hidden" id="lecturex" name="lecturex" value="1">
<input type="hidden" id="labx" name="labx" value="1">
<input type="hidden" id="discussionx" name="discussionx" value="1">
<input type="hidden" id="seminarx" name="seminarx" value="1">
<input type="hidden" id="workshopx" name="workshopx" value="1">
<input type="hidden" id="elearningx" name="elearningx" value="1">
<input type="hidden" id="lec_othersx" name="lec_othersx" value="1">

<input type="hidden" id="W_codew" name="W_code[]" value="">
<input type="hidden" id="U_codew" name="U_code[]" value="">
<input type="hidden" id="K_codew" name="K_code[]" value="">
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
<table class=\'table table-bordered table-hover\'>
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

              $( "#dialogw1" ).dialog({
                autoOpen: false,
                show: {
                  effect: "blind",
                  duration: 500
                },
                height:"auto",
                width:"90%"
              });
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
              $("div#add_knowledge").append("<div id=\'dialogw" + knowledgex + "\' title=\'Code Description\'><form><select id=\'W" + knowledgex + "_codex\' name=\'W_codex[]\'>' . $course_code_empty . '</select><input type=\'button\' value=\'Ok\' onclick=\'close_dialog1(" + knowledgex + ");\'></form></div><table class=\'table table-bordered table-hover\'><tr><td>W" + knowledgex + "</td><td><input type=\'hidden\' id=\'W" + knowledgex + "_code\' name=\'W_code[]\'><textarea id=\'W_outcomes[]\' name=\'W_outcomes[]\'></textarea></td><td><select id=\'W" + knowledgex + "_assmeths\' name=\'W" + knowledgex + "_assmeths\' onchange=\'knowledge_onblur(" + knowledgex + ")\'>' . $course_assmethx . '</select></td><td><form><input type=\'button\' value=\'Code\' onclick=\'dialog1(" + knowledgex + ");\'></form></td><td><p id=\'labelw_" + knowledgex + "\'></p></td></tr></table>");

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
                  $("#dialogw" + x).dialog( "close" );
                }
          </script>
        </div>
        <div id = "skills">
          <div id="add_skill"></div>
          <script>
            $(document).ready(function() {
              $("div#add_skill").html("' . $course_skill . '");

              $( "#dialogu1" ).dialog({
                autoOpen: false,
                show: {
                  effect: "blind",
                  duration: 500
                },
                height:"auto",
                width:"90%"
              });
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
            
                $("div#add_skill").append("<div id=\'dialogu" + skillx + "\' title=\'Code Description\'><form><select id=\'U" + skillx + "_codex\' name=\'U_codex[]\'>' . $course_code_empty . '</select><input type=\'button\' value=\'Ok\' onclick=\'close_dialog2(" + skillx + ");\'></form></div><table class=\'table table-bordered table-hover\'><tr><td>U" + skillx + "</td><td><input type=\'hidden\' id=\'U" + skillx + "_code\' name=\'U_code[]\'><textarea id=\'U_outcomes[]\' name=\'U_outcomes[]\'></textarea></td><td><select id=\'U" + skillx + "_assmeths\' name=\'U" + skillx + "_assmeths\' onchange=\'skill_onblur(" + skillx + ")\'>' . $course_assmethx . '</select></td><td><form><input type=\'button\' value=\'Code\' onclick=\'dialog2(" + skillx + ");\'></form></td><td><p id=\'labelu_" + skillx + "\'></p></td></tr></table>");
            
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

              $( "#dialogk1" ).dialog({
                autoOpen: false,
                show: {
                  effect: "blind",
                  duration: 500
                },
                height:"auto",
                width:"90%"
              });
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
            
              $("div#add_social").append("<div id=\'dialogk" + socialx + "\' title=\'Code Description\'><form><select id=\'K" + socialx + "_codex\' name=\'K_codex[]\'>' . $course_code_empty . '</select><input type=\'button\' value=\'Ok\' onclick=\'close_dialog3(" + socialx + ");\'></form></div><table class=\'table table-bordered table-hover\'><tr><td>K" + socialx + "</td><td><input type=\'hidden\' id=\'K" + socialx + "_code\' name=\'K_code[]\'><textarea id=\'K_outcomes[]\' name=\'K_outcomes[]\'></textarea></td><td><select id=\'K" + socialx + "_assmeths\' name=\'K" + socialx + "_assmeths\' onchange=\'social_onblur(" + socialx + ")\'>' . $course_assmethx . '</select></td><td><form><input type=\'button\' value=\'Code\' onclick=\'dialog3(" + socialx + ");\'></form></td><td><p id=\'labelk_" + socialx + "\'></p></td></tr></table>");
            
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
      function knowledge_onblur(y) {
        var x = "w" + y;
        var name = $("#W" + y + "_assmeths option:selected").text();

        if($("#" + x).length == 0) {
          $("#add_assmethw").append("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'text\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
        } else {
          $("#" + x).html("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'text\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
        }
      }

      function skill_onblur(y) {
        var x = "u" + y;
        var name = $("#U" + y + "_assmeths option:selected").text();

        if($("#" + x).length == 0) {
          $("#add_assmethw").append("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'text\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
        } else {
          $("#" + x).html("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'text\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
        }
      }

      function social_onblur(y) {
        var x = "k" + y;
        var name = $("#K" + y + "_assmeths option:selected").text();

        if($("#" + x).length == 0) {
          $("#add_assmethw").append("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'text\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
        } else {
          $("#" + x).html("<table class=\'table table-bordered table-hover\' id=\'" + x + "\'><tr><td></td><td colspan=\'2\'>" + name + "</td><td colspan=\'2\'><input type=\'text\' id=\'percent[]\' name=\'percent[]\'></td></tr></table>");
        }
      }
    </script>');
$form["general_info_c"] = array(
  '#markup' => '
  <script>
      $(document).ready(function() {
        $("#add_others").html("<input type=\'hidden\' id=\'others\' value=\'2\'><input type=\'hidden\' id=\'workloads\' value=\'1\'><input type=\'hidden\' id=\'workloads2\' value=\'1\'><table class=\'table table-bordered table-hover\'><tbody><tr><th colspan = \'4\'>C. Readings</th></tr><tr><td>C.1</td><td>Compulsory readings</td><td colspan = \'2\'><textarea id=\'compulsory\' name=\'compulsory\' style=\'height: 70px; width: 250px;\'></textarea></td></tr><tr><td>C.2</td><td>Supplementary readings</td><td><textarea id=\'supplementary\' name=\'supplementary\' style=\'height: 70px; width: 250px;\'></textarea></td><td><form><input type=\'button\' onclick=\'otherw()\' value=\'Add more\'></form></td></tr></tbody></table>");
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
            $("#add_workload").html("<table class=\'table table-bordered table-hover\'><tbody><tr><th colspan = \'5\'>D. Student workload</th></tr><tr><td>D.1</td><td colspan=\'3\'>ECTS Credits</td><td><input type=\'number\' name=\'ects\'></td></tr></tbody></table>");
          });

          // function workloadw() {
          //   var workloads = $("#workloads").val();
          //   workloads++;
          //   $("#workloads").val(workloads);

          //   var workloads2 = $("#workloads2").val();
          //   workloads2++;
          //   $("#workloads2").val(workloads2);

          //   $("#add_workload").append("<table class=\'table table-bordered table-hover\'><tbody><tr><td></td><td><input type=\'text\' name=\'ws_activity[]\'></td><td><input type=\'number\' id=\'ws_hour" + (workloads - 1) + "\' name=\'ws_hour[]\' onblur=\'workload_onblur()\'> h</td><td><input type=\'number\' id=\'ws_hour2" + (workloads2 - 1) + "\' name=\'ws_hour2[]\' onblur=\'workload_onblur()\'> h</td></tr></tbody></table>");
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
    <td><select name="course_coordinator">' . $course_coordinator . '</select></td>
  </tr>
  <tr>
    <td>E.2</td>
    <td> Academic Teacher</td>
    <td><select id="course_teacher" name="course_teacher">' . $course_teacher . '</select><br>
        <select id="course_teacher2" name="course_teacher2">' . $course_teacher2 . '</select><br>
        <select id="course_teacher3" name="course_teacher3">' . $course_teacher3 . '</select></td>
  </tr>
  <tr>
    <td>E.4</td>
    <td>Date of Preparation(latest submission date)</td>
    <td><input type="text" id="pre_date" name="pre_date" readonly>
      <script>
      $("#pre_date").val(Date());
      </script></td>
  </tr>
</table>');

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Add Course'
		);

	return $form;
}

function new_course_page_submit($form, $form_state) {
  $idx = filter_input(INPUT_GET, 'idx');

  $course_name = htmlspecialchars($_POST['course_name']);

// A
  $course_code = htmlspecialchars($_POST['course_code']);
  $year = htmlspecialchars($_POST['year']);
  $language = htmlspecialchars($_POST['language']);
  // $coor_department = htmlspecialchars($_POST['coor_department']);
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
  if (!is_numeric(htmlspecialchars($_POST['ects']))) {
    $ects = 0;
  } else {
    $ects = htmlspecialchars($_POST['ects']);
  }
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

  global $user;
  $department = db_query("SELECT {id} FROM {syllabus_main_department} WHERE {hod}='" . $user -> uid . "' LIMIT 1") -> fetchField();

	$id = db_insert('syllabus_main_course') -> fields(array(
		'name' => $course_name,
		'code' => $course_code,
    'year' => $year,
		'lang' => $language,
    'dep' => $department,
		'field' => $study,
		'degree' => $profile,
		'mode' => $mode,
		'level' => $level,
		'prere' => $prere,
    'prere2' => $prere2,
    'prere3' => $prere3,
		'objective' => $objective,
		'w_outcome' => $W_outcomes,
		'w_assmeth'  => $W_assmeths,
		'w_code' => $W_codes,
    'w_desc' => '',
		'u_outcome' =>  $U_outcomes,
		'u_assmeth'  => $U_assmeths,
		'u_code' => $U_codes,
    'u_desc' => '',
		'k_outcome'  => $K_outcomes,
		'k_assmeth'  => $K_assmeths,
		'k_code'  => $K_codes,
    'k_desc' => '',
		'lecture'  => $lecture,
		'lab'  => $lab,
		'discussion'  => $discussion,
		'seminar'  => $seminar,
		'workshop'  => $workshop,
		'elearning'  => $elearning,
    'lec_other' => $lec_other,
    'percent' => $percent,
		'compulsory'  => $compulsory,
		'supplementary'  => $supplementary,
		'other_name'  => $other_name,
		'other'  => $other,
    'ects' => $ects,
    'ws_hour' => $ws_hour,
		'ws_activity'  => $ws_activity,
    'ws_non_con_hour' => $ws_hour2,
    'coordinator' => $course_coordinator,
		'teacher' => $course_teacher,
    'pre_date'  => $pre_date,
    'note' => '',
		'status' => 0
		)) -> execute();
	drupal_set_message('New Course has been created!');
}

