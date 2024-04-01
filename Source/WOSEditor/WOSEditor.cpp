#include "WOSEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "Gizmo/CustomVisualizer.h"
#include "Gizmo/MapLayoutViewer.h"

IMPLEMENT_GAME_MODULE(FWOSEditorModule, WOSEditor);

void FWOSEditorModule::StartupModule()
{
    // Check if editor is valid
    if (GUnrealEd)
    {
        TSharedPtr<CustomVisualizer> Visualizer = MakeShared<CustomVisualizer>();
        GUnrealEd->RegisterComponentVisualizer(UStaticMeshComponent::StaticClass()->GetFName(), Visualizer);
        GUnrealEd->RegisterComponentVisualizer(UMapLayoutViewer::StaticClass()->GetFName(), Visualizer);
    }
}

void FWOSEditorModule::ShutdownModule()
{
    // Check if editor is valid
    if (GUnrealEd)
    {
        GUnrealEd->UnregisterComponentVisualizer(UStaticMeshComponent::StaticClass()->GetFName());
        GUnrealEd->UnregisterComponentVisualizer(UMapLayoutViewer::StaticClass()->GetFName());
    }
}