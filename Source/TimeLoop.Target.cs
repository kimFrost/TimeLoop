using UnrealBuildTool;
using System.Collections.Generic;

public class TimeLoopTarget : TargetRules
{
	public TimeLoopTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "TimeLoop" } );
	}
}
