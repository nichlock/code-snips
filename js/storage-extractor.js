/* Extracts and downloads all possible variables from the `obj_to_download` object. */

function downloadStorage(obj_to_download=globalThis) {
  var combined = {}

  for (var key in obj_to_download) {
    try{
    combined[key] = JSON.parse(JSON.stringify(obj_to_download[key]));
    }catch(e){};
  }

  var element = document.createElement('a');
  element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(JSON.stringify(combined)));
  element.setAttribute('download', 'mem-dump.json');

  element.style.display = 'none';
  document.body.appendChild(element);

  element.click();

  document.body.removeChild(element);
}

downloadStorage();
