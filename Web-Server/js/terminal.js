var command ;
jQuery(function($) {
  $('html').terminal(function(cmd, term) {
	console.log("command from terminal.js :" + cmd);
    if (cmd == 'help') {
      term.echo("available commands are mysql, js, test");
    } else if (cmd == 'test'){
      term.push(function(cmd, term) {
        if (command == 'help') {
          term.echo('type "ping" it will display "pong"');
        } else if (cmd == 'ping') {
          term.echo('pong');
        } else {
          term.echo('unknown command "' + cmd + '"');
        }
      }, {
        prompt: 'test> ',
        name: 'test'});
    } else if (command == "js") {
      term.push(function(command, term) {
        var result = window.eval(command);
        if (result != undefined) {
          term.echo(String(result));
        }
      }, {
        name: 'js',
        prompt: 'js> '});
      } else if (command == 'mysql') {
        term.push(function(command, term) {
          term.pause();
          //$.jrpc is helper function which
          //creates json-rpc request
          $.jrpc("mysql-rpc-demo.php",
            "query",
            [command],
            function(data) {
              term.resume();
              if (data.error) {
                if (data.error.error && data.error.error.message) {
                  term.error(data.error.error.message); // php error
                } else {
                  term.error(data.error.message); // json rpc error
                }
              } else {
                if (typeof data.result == 'boolean') {
                  term.echo(data.result ?
                            'success' :
                            'fail');
                } else {
                  var len = data.result.length;
                  for(var i=0;i<len; ++i) {
                    term.echo(data.result[i].join(' | '));
                  }
                }
              }
            },
            function(xhr, status, error) {
              term.error('[AJAX] ' + status +
                         ' - Server reponse is: \n' +
                         xhr.responseText);
                         term.resume();
                   }); // rpc call
          }, {
            greetings: "This is example of using mysql"+
              " from terminal\n you are allowed to exe"+
              "cute: select, insert, update and delete"+
              " from/to table:\n   table test(integer_"+
              "value integer, varchar_value varchar(255))",
            prompt: "mysql> "});
          } else {
            term.echo("unknow command " + command);
          }
        }, {
          greetings: "multiple terminals demo use help"+
                " to see available commands"
       });});