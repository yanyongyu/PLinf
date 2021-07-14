var $ = mdui.$;
var opcode_list = [];

/** @param {string[][]} symbol */
function refresh_symbol(symbol) {
  $("#symbol-table-body").empty();
  symbol.map((value) => {
    $("#symbol-table-body").append(
      $("<tr></tr>")
        .append($("<td></td>").text(value[0]))
        .append($("<td></td>").append(colorize_symbol(value[1])))
        .append($("<td></td>").text(value[2]))
        .append($("<td></td>").text(value[3]))
    );
  });
  mdui.mutation();
}

/** @param {string[][]} stack */
function refresh_stack(stack) {
  $("#stack-table-body").empty();
  stack.map((value) => {
    $("#stack-table-body").append(
      $("<tr></tr>").append(
        $("<td></td>").append(colorize_stack(value[0], value[1]))
      )
    );
  });
  mdui.mutation();
}

/** @param {string[]} current */
function refresh_current(current) {
  $("#current-table-body").empty();
  $("#current-table-body").append(
    $("<tr></tr>")
      .append($("<td></td>").text(current[0]))
      .append($("<td></td>").text(current[1]))
      .append($("<td></td>").append(colorize_argument(current[2], current[3])))
  );
}

/** @param {string} output */
function refresh_output(output) {
  $("#output > pre").text(output);
}

/** @param {string} code */
function init_code(code) {
  mdui.$("#code > pre").text(code);
}

/** @param {string[][]} opcode */
function init_opcode(opcode) {
  opcode_list = opcode;
  $("#opcode-table-body").empty();
  opcode.map((value, index) => {
    $("#opcode-table-body").append(
      $(`<tr id="opcode-${index}"></tr>`)
        .append($("<td></td>").text(value[0]))
        .append($("<td></td>").text(value[1]))
        .append($("<td></td>").append(colorize_argument(value[2], value[3])))
    );
  });
  mdui.mutation();
}

/** @param {number} index */
function refresh_opcode(index) {
  $("#opcode-table-body > tr").removeAttr("opcode-current");
  refresh_current(opcode_list[index]);
  $(`#opcode-${index}`).attr("opcode-current", true);
  // TODO: auto scroll
  // $(`#opcode-${index}`).offset({ top: 300 });
}

/** @param {string} tree */
function init_tree(tree) {
  $("#tree > pre").text(tree);
}

/** @param {string} type
 *  @return {string}
 */
function colorize_symbol(type) {
  switch (type) {
    case "const":
      return `<span class="mdui-text-color-light-blue"><strong>const</strong></span>`;
    case "type":
      return `<span class="mdui-text-color-cyan"><strong>type</strong></span>`;
    case "variable":
      return `<span class="mdui-text-color-green"><strong>var</strong></span>`;
    case "procedure":
      return `<span class="mdui-text-color-red"><strong>proc</strong></span>`;
    case "function":
      return `<span class="mdui-text-color-purple"><strong>func</strong></span>`;
  }
}

/** @param {string} type
 *  @param {string} value
 *  @return {string}
 */
function colorize_stack(type, value) {
  switch (type) {
    case "const":
      return $(`<span class="mdui-text-color-light-blue"></span>`).append(
        $("<strong></strong>").text(value)
      );
    case "type":
    case "type_array":
      return $(`<span class="mdui-text-color-cyan"></span>`).append(
        $("<strong></strong>").text(value)
      );
    case "var":
      return $(`<span class="mdui-text-color-green"></span>`).append(
        $("<strong></strong>").text(value)
      );
    case "block":
      return $(`<span class="mdui-text-color-red"></span>`).append(
        $("<strong></strong>").text(value)
      );
    case "param":
      return $(`<span class="mdui-text-color-purple"></span>`).append(
        $("<strong></strong>").text(value)
      );
  }
}

/** @param {string} type
 *  @param {string} value
 *  @return {string}
 */
function colorize_argument(type, value) {
  switch (type) {
    case "int":
      return $(`<span class="mdui-text-color-light-blue"></span>`).append(
        $("<strong></strong>").text(value)
      );
    case "real":
      return $(`<span class="mdui-text-color-cyan"></span>`).append(
        $("<strong></strong>").text(value)
      );
    case "bool":
      return $(`<span class="mdui-text-color-green"></span>`).append(
        $("<strong></strong>").text(value)
      );
    case "str":
      return $(`<span class="mdui-text-color-red"></span>`).append(
        $("<strong></strong>").text(value)
      );
    case "type":
      return $(`<span class="mdui-text-color-purple"></span>`).append(
        $("<strong></strong>").text(value)
      );
    case "null":
      return $(`<span class="mdui-text-color-grey"></span>`).append(
        $("<strong></strong>").text(value)
      );
    default:
      return "";
  }
}

function do_execute() {
  if (!window.con) {
    alert("Cannot connect to the compiler!");
    return;
  }
  window.con.do_execute();
}

function reset() {
  if (!window.con) {
    alert("Cannot connect to the compiler!");
    return;
  }
  window.con.reset();
  $("#next").removeAttr("disabled");
}

function finished() {
  alert("运行完毕");
  $("#next").attr("disabled", true);
}

$(function () {
  new QWebChannel(qt.webChannelTransport, function (channel) {
    window.con = channel.objects.con;
  });
});

// init_opcode([["0", "opcode_load_fast", "str", "123"]]);
// refresh_opcode(0);
// refresh_symbol([["asd", "variable", "123", "0"]]);
// refresh_stack([["param", "param1:real"]]);
