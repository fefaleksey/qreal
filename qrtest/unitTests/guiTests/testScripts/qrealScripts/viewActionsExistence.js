/* Copyright 2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

// For autocompletion and syntax highlighting
var mainWindow, ui, utils, keyboard, palette, hints, scene, cursor;

var menu_View = ui.getMenu("menu_View");
assert(menu_View != null);

utils.activateMenu(menu_View);
api.wait(200);

var actionFullscreen = ui.getActionInMenu(menu_View, "actionFullscreen");
checkAction(actionFullscreen, true, false, false);
expect(!ui.isSubMenuInMenu(menu_View, actionFullscreen));

var actionZoom_In = ui.getActionInMenu(menu_View, "actionZoom_In");
checkAction(actionZoom_In, false, false, false);
expect(!ui.isSubMenuInMenu(menu_View, actionZoom_In));

var actionZoom_Out = ui.getActionInMenu(menu_View, "actionZoom_Out");
checkAction(actionZoom_Out, false, false, false);
expect(!ui.isSubMenuInMenu(menu_View, actionZoom_Out));

var actionShowSplash = ui.getActionInMenu(menu_View, "actionShowSplash");
checkAction(actionShowSplash, true, true, false);
expect(!ui.isSubMenuInMenu(menu_View, actionShowSplash));

var actionMenuPanels = ui.getActionInMenu(menu_View, "Panels");
checkAction(actionMenuPanels, true, false, false);
expect(ui.isSubMenuInMenu(menu_View, actionMenuPanels));

utils.activateMenuAction(menu_View, actionMenuPanels);
api.wait(200);

var subMenuPanels = ui.getMenuContainedByAction(actionMenuPanels);
assert(subMenuPanels != null);

function expectPanelsAction(actionName, isChecked) {
    var action = ui.getActionInMenu(subMenuPanels, actionName);
    checkAction(action, true, true, isChecked);
    expect(!ui.isSubMenuInMenu(subMenuPanels, action));
}

expectPanelsAction("Mini Map", false);
expectPanelsAction("Palette", true);
expectPanelsAction("Logical Model Explorer", false);
expectPanelsAction("Errors", false);
expectPanelsAction("Graphical Model Explorer", false);
expectPanelsAction("Property Editor", false);
expectPanelsAction("File Toolbar", true);
expectPanelsAction("Edit Toolbar", true);
expectPanelsAction("View Toolbar", true);
expectPanelsAction("Interpreter Toolbar", false);
expectPanelsAction("Generators Toolbar", false);
