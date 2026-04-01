using UnrealBuildTool;

public class WebAdventure : ModuleRules
{
    public WebAdventure(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "EnhancedInput",
                "UMG",
                "Slate",
                "SlateCore",
                "AIModule"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "GameplayTasks"
            }
        );
    }
}

