/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * Produced by:
 *      Mykola Konyk
 *      Side Effects Software Inc
 *      123 Front Street West, Suite 1401
 *      Toronto, Ontario
 *      Canada   M5J 2M2
 *      416-504-9876
 *
 */

#pragma once


struct FGeometry;
struct FSlateBrush;
struct FPointerEvent;


class FAssetData;
class UStaticMesh;
class IDetailLayoutBuilder;
class UHoudiniAssetComponent;


/** Hashing function for our pair. **/
uint32 GetTypeHash(TPair<UStaticMesh*, int32> Pair);


class FHoudiniAssetComponentDetails : public IDetailCustomization
{
public:

	/** Constructor. **/
	FHoudiniAssetComponentDetails();

public: /** IDetailCustomization methods. **/

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

public:

	/** Create an instance of this detail layout class. **/
	static TSharedRef<IDetailCustomization> MakeInstance();

public:

	/** Desired width for row value widget. **/
	static float RowValueWidgetDesiredWidth;

private:

	/** Button click handlers. **/	
	FReply OnButtonClickedBakeSingle();

private:

	/** Helper method used to create widgets for generated static meshes. **/
	void CreateStaticMeshAndMaterialWidgets(IDetailCategoryBuilder& DetailCategoryBuilder);

	/** Helper method used to create a single static mesh. **/
	void CreateSingleStaticMesh();

	/** Gets the border brush to show around thumbnails, changes when the user hovers on it. **/
	const FSlateBrush* GetStaticMeshThumbnailBorder(UStaticMesh* StaticMesh) const;
	const FSlateBrush* GetMaterialInterfaceThumbnailBorder(UMaterialInterface* MaterialInterface) const;

	/** Handler for when static mesh thumbnail is double clicked. We open editor in this case. **/
	FReply OnThumbnailDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent, UObject* Object);

	/** Handler for bake individual static mesh action. **/
	FReply OnBakeStaticMesh(UStaticMesh* StaticMesh, UHoudiniAssetComponent* HoudiniAssetComponent);

	/** Handler for bake all static meshes action. **/
	FReply OnBakeAllStaticMeshes();

	/** Delegate used to detect if valid object has been dragged and dropped. **/
	bool OnMaterialInterfaceDraggedOver(const UObject* InObject) const;

	/** Delegate used when valid material has been drag and dropped. **/
	void OnMaterialInterfaceDropped(UObject* InObject, UStaticMesh* StaticMesh, int32 MaterialIdx);

	/** Construct drop down menu content for material. **/
	TSharedRef<SWidget> OnGetMaterialInterfaceMenuContent(UMaterialInterface* MaterialInterface, UStaticMesh* StaticMesh, int32 MaterialIdx);

	/** Delegate for handling selection in content browser. **/
	void OnMaterialInterfaceSelected(const FAssetData& AssetData, UStaticMesh* StaticMesh, int32 MaterialIdx);

	/** Closes the combo button. **/
	void CloseMaterialInterfaceComboButton();

	/** Browse to material interface. **/
	void OnMaterialInterfaceBrowse(UMaterialInterface* MaterialInterface);

	/** Handler for reset material interface button. **/
	FReply OnResetMaterialInterfaceClicked(UStaticMesh* StaticMesh, int32 MaterialIdx);

private:

	/** Components which are being customized. **/
	TArray<UHoudiniAssetComponent*> HoudiniAssetComponents;

	/** Map of static meshes and corresponding thumbnail borders. **/
	TMap<UStaticMesh*, TSharedPtr<SBorder> > StaticMeshThumbnailBorders;

	/** Map of static meshes / material indices to combo elements. **/
	TMap<TPair<UStaticMesh*, int32>, TSharedPtr<SComboButton> > MaterialInterfaceComboButtons;

	/** Delegate for filtering material interfaces. **/
	FOnShouldFilterAsset OnShouldFilterMaterialInterface;

	/** Whether baking option is enabled. **/
	bool bEnableBaking;
};
