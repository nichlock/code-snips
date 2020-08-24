/* HOW TO USE THIS:
 * Go on the labels page (eg https://github.com/CuUwrRobotics/repo-name/labels)
 * Paste this script in your inspect-element console
 * Press Enter and spam Space until it's done!
 * This will automatically remove the default labels and add the new ones. Existing labels will be updated.
 *
 * To change the labels this uses, either manually change the labels listed OR use the file export-labels.js to get 
 * existing labels as an array with all data, then paste the new ones into the to_add array.
 *
 * By default, the labels that GitHub auto-populates are removed.
 *
 * Based on code within https://gist.github.com/Isaddo/7efebcb673a0957b9c6f07cd14826ea4
 */

var to_remove  = [
{ "name": "bug" },
{ "name": "documentation" },
{ "name": "duplicate" },
{ "name": "enhancement" },
{ "name": "good first issue" },
{ "name": "help wanted" },
{ "name": "invalid" },
{ "name": "question" },
{ "name": "wontfix" },
]
to_remove.forEach(function(label) {
  removeLabel(label)
})

var to_add = [
  {
    "name": "area/documentation",
    "description": "Improvements or additions to documentation",
    "color": "eeeeee"
  },
  {
    "name": "area/github",
    "description": "Related to GitHub setup, not code",
    "color": "eeeeee"
  },
  {
    "name": "area/hardware",
    "description": "Related to the hardware communication or cicuit board",
    "color": "eeeeee"
  },
  {
    "name": "area/machine-vision",
    "description": "Related to machine vision",
    "color": "eeeeee"
  },
  {
    "name": "area/motion",
    "description": "Related to the motion of the robot",
    "color": "eeeeee"
  },
  {
    "name": "area/ros",
    "description": "Related to ROS configurations, builds, installs, etc.",
    "color": "eeeeee"
  },
  {
    "name": "good first issue",
    "description": "Good for newcomers",
    "color": "0e8a16"
  },
  {
    "name": "help wanted",
    "description": "Extra attention is needed",
    "color": "fbca04"
  },
  {
    "name": "kind/bug",
    "description": "Something isn't working",
    "color": "1d76db"
  },
  {
    "name": "kind/enhancement",
    "description": "Improvement to existing code",
    "color": "1d76db"
  },
  {
    "name": "kind/feature",
    "description": "Features to be added",
    "color": "1d76db"
  },
  {
    "name": "kind/planning",
    "description": "For planning a future development",
    "color": "1d76db"
  },
  {
    "name": "level/advanced",
    "description": "You'll want a good background in programming and/or the package",
    "color": "7fe3e1"
  },
  {
    "name": "level/beginner",
    "description": "Little programming knowledge needed",
    "color": "7fe3e1"
  },
  {
    "name": "level/medium",
    "description": "A little programming knowledge will help, but you won't need any advanced concepts",
    "color": "7fe3e1"
  },
  {
    "name": "question",
    "description": "More info wanted regarding a problem or package",
    "color": "d876e3"
  },
  {
    "name": "vital",
    "description": "Other issues/work rely on this issue",
    "color": "b60205"
  },
  {
    "name": "wontfix",
    "description": "This will not be worked on",
    "color": "000000"
  }
];
to_add.forEach(function(label) {
  addLabel(label)
})
// One time doesen't always work! This is a brute force fix. This issue can be fixed by simply changing the program to not delete labels that will be created again. I don't have the time though.
to_add.forEach(function(label) {
  addLabel(label)
})

function removeLabel(label) {
  [].slice.call(document.querySelectorAll(".js-labels-list-item"))
  .forEach(function(element) {
    if (element.querySelector('.js-label-link').textContent.trim() === label.name) {
      element.querySelector('.js-delete-label').querySelector(".btn-link").click()
    }
  })
}

function updateLabel (label) {
  var flag = false;
  [].slice.call(document.querySelectorAll(".js-labels-list-item"))
  .forEach(function(element) {
    if (element.querySelector('.js-label-link').textContent.trim() === label.name) {
      flag = true
      element.querySelector('.js-edit-label').click()
      element.querySelector('.js-new-label-name-input').value = label.name
      element.querySelector('.js-new-label-description-input').value = label.description
      element.querySelector('.js-new-label-color-input').value = '#' + label.color
      element.querySelector('.js-edit-label-cancel ~ .btn-primary').click()
    }
  })
  return flag
}

function addNewLabel (label) {
  document.querySelector('.js-new-label-name-input').value = label.name
  document.querySelector('.js-new-label-description-input').value = label.description
  document.querySelector('.js-new-label-color-input').value = '#' + label.color
  document.querySelector('.js-details-target ~ .btn-primary').disabled = false
  document.querySelector('.js-details-target ~ .btn-primary').click()
}

function addLabel (label) {
  if (!updateLabel(label)) addNewLabel(label)
}
