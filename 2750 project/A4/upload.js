$(document).ready(function() {
    $('#upload-form').submit(function(event) {
      event.preventDefault();
  
      var formData = new FormData(this);
  
      $.ajax({
        url: '/upload',
        type: 'POST',
        data: formData,
        processData: false,
        contentType: false,
        success: function(response) {
          console.log('File uploaded successfully.');
        },
        error: function(jqXHR, textStatus, errorThrown) {
          console.error('Error uploading file:', errorThrown);
        }
      });
    });
  });