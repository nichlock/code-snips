/* HOW TO USE THIS:
 * Go on the labels page (eg https://github.com/CuUwrRobotics/repo-name/labels)
 * Paste this script in your inspect-element console
 * Press Enter
 *
 * To be used with import-labels.js.
 * Exports labels, descriptions, and colors to a JS array so it can be copied to another repository.
 * From https://gist.github.com/MoOx/93c2853fee760f42d97f
 */

var labels = [];
[].slice.call(document.querySelectorAll(".js-label-link"))
.forEach(function(element) {
  labels.push({
    name: element.textContent.trim(),
    description: element.getAttribute("title"),
    // using style.backgroundColor might returns "rgb(...)"
    color: element.getAttribute("style")
      .replace("background-color:", "")
      .replace(/color:.*/,"")
      .trim()
      // github wants hex code only without # or ;
      .replace(/^#/, "")
      .replace(/;$/, "")
      .trim(),
  })
})

console.log(JSON.stringify(labels, null, 2))
