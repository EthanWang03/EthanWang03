/* javascript to accompany jquery.html */

$(document).ready( 
  /* this defines a function that gets called after the document is in memory */
  function()
  {

    /* add a click handler for our button */
    $("#button").click(
      function()
      {
	/* ajax post */
	$.post("/form_handler.html",
	  /* pass a JavaScript dictionary */
	  {
	    name: $("#name").val(),	/* retreive value of name field */
	    extra_info: "some stuff here"
	  },
	  function( data, status )
	  {
	    alert( "Data: " + data + "\nStatus: " + status );
	  }
	);
      }
    );
  }
);
