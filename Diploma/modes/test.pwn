native CreateButton(x, y, w, h, text[]);
native DebugFunc();

forward OnGameStarted();

public OnGameStarted(){
	DebugFunc();
	CreateButton(100, 100, 120, 60, "PUSH!");
	CreateButton(230, 100, 120, 60, "TWO");
	CreateButton(100, 170, 120, 60, "THREE");
	CreateButton(230, 170, 120, 60, "FOUR");
	return 0;
}
