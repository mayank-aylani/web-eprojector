
function changeColor(color) {
const parts = ['head', 'body', 'arms', 'left-leg', 'right-leg'];

parts.forEach(function(id) {
const element = document.getElementById(id);
element.style.borderColor = color;
element.style.backgroundColor = color;
});
}
