/* MainPanel.h
Copyright (c) 2014 by Michael Zahniser

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/

#ifndef MAIN_PANEL_H_
#define MAIN_PANEL_H_

#include "Panel.h"

#include "Command.h"
#include "Engine.h"

class PlayerInfo;
class ShipEvent;



// Class representing the main panel (i.e. the view of your ship moving around).
// The goal is that the Engine class will not need to know about displaying
// panels or handling key presses; it instead focuses just on the calculations
// needed to move the ships around and to figure out where they should be drawn.
class MainPanel : public Panel {
public:
	explicit MainPanel(PlayerInfo &player);
	
	virtual void Step() override;
	virtual void Draw() override;
	
	// The planet panel calls this when it closes.
	void OnCallback();
    
#ifdef TOUCH_VERSION
    void TouchButtonAction(Command command);
    void LoadTouchControl(const char * path, const char * name, Point off, int width, int height);
#endif
	
	
protected:
	// Only override the ones you need; the default action is to return false.
	virtual bool KeyDown(SDL_Keycode key, Uint16 mod, const Command &command) override;
	virtual bool Click(int x, int y, int clicks) override;
	virtual bool RClick(int x, int y) override;
	virtual bool Drag(double dx, double dy) override;
	virtual bool Release(int x, int y) override;
	virtual bool Scroll(double dx, double dy) override;
	
	
private:
	void ShowScanDialog(const ShipEvent &event);
	bool ShowHailPanel();
	
	
private:
	PlayerInfo &player;
	
	Engine engine;
	
	Command show;
	
	double load;
	double loadSum;
	int loadCount;
	
	Point dragSource;
	Point dragPoint;
	bool isDragging = false;
	bool hasShift = false;
	bool canClick = false;
	bool canDrag = false;
};



#endif
