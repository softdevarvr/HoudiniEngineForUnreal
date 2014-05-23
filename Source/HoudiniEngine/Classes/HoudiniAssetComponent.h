/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * Produced by:
 *      Damian Campeanu
 *      Side Effects Software Inc
 *      123 Front Street West, Suite 1401
 *      Toronto, Ontario
 *      Canada   M5J 2M2
 *      416-504-9876
 *
 */

#pragma once
#include "HAPI.h"
#include "HoudiniAssetComponent.generated.h"

class UClass;
class UMaterial;
class FTransform;
class UHoudiniAsset;
class FPrimitiveSceneProxy;
class FComponentInstanceDataCache;

struct FPropertyChangedEvent;

//UCLASS(HeaderGroup=Component, ClassGroup=(Rendering, Common), hidecategories=(Object,Activation,"Components|Activation"), ShowCategories=(Mobility), dependson=ULightmassPrimitiveSettingsObject, editinlinenew, meta=(BlueprintSpawnableComponent))
UCLASS(HeaderGroup=Component, ClassGroup=(Rendering, Common), hidecategories=(Object,Activation,"Components|Activation"), ShowCategories=(Mobility), editinlinenew, meta=(BlueprintSpawnableComponent))
class HOUDINIENGINE_API UHoudiniAssetComponent : public UMeshComponent
{
	friend class FHoudiniMeshSceneProxy;

	GENERATED_UCLASS_BODY()

	/** **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HoudiniAsset, ReplicatedUsing = OnRep_HoudiniAsset)
	UHoudiniAsset* HoudiniAsset;
	
	/** **/
	UFUNCTION()
	void OnRep_HoudiniAsset(UHoudiniAsset* OldHoudiniAsset);

	/** Change the Houdini asset used by this instance. **/
	UFUNCTION(BlueprintCallable, Category = "Components|HoudiniAsset")
	virtual bool SetHoudiniAsset(UHoudiniAsset* NewHoudiniAsset);
		
public:

	/** Used to differentiate native components from dynamic ones. **/
	void SetNative(bool InbIsNativeComponent);

public:

	/** Callback used by cooking to notify about cooking results. **/
	void CookingCompleted(HAPI_AssetId InAssetId, const char* AssetName);

	/** Callback used by cooking to notify about errors. **/
	void CookingFailed();

public: /** UObject methods. **/

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) OVERRIDE;

protected: /** UActorComponent methods. **/

	virtual void OnComponentCreated() OVERRIDE;
	virtual void OnComponentDestroyed() OVERRIDE;

	virtual void OnRegister() OVERRIDE;
	virtual void OnUnregister() OVERRIDE;

	virtual void GetComponentInstanceData(FComponentInstanceDataCache& Cache) const OVERRIDE;
	virtual void ApplyComponentInstanceData(const FComponentInstanceDataCache& Cache) OVERRIDE;

	//virtual void BeginDestroy() OVERRIDE;
	//virtual void FinishDestroy() OVERRIDE;

private: /** UPrimitiveComponent methods. **/

	virtual FPrimitiveSceneProxy* CreateSceneProxy() OVERRIDE;

private: /** UMeshComponent methods. **/

	virtual int32 GetNumMaterials() const OVERRIDE;

private: /** UsceneComponent methods. **/

	//virtual bool MoveComponent( const FVector& Delta, const FRotator& NewRotation, bool bSweep, FHitResult* OutHit=NULL, EMoveComponentFlags MoveFlags = MOVECOMP_NoFlags ) OVERRIDE;
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const OVERRIDE;

protected:

	/** Monkey patching: given a new class instance, patch class information of this. **/
	void MonkeyPatchClassInformation(UClass* ClassInstance);

	/** Monkey patching: translate asset parameters to class properties and insert them into a given class instance. **/
	void MonkeyPatchCreateProperties(UClass* ClassInstance);

	/** Monkey patching: helper function used by property creation to generate array sub properties. **/
	void MonkeyPatchArrayProperties(UArrayProperty* ArrayProperty);

protected:

	/** Map holding a list of monkey patched classes and corresponding houdini asset instances. **/
	static TMap<UHoudiniAsset*, UClass*> AssetClassRegistry;
	
protected:
	
	/** Triangle data used for rendering in viewport / preview window. **/
	TArray<FHoudiniMeshTriangle> HoudiniMeshTris;

	/** Bounding volume information for current geometry. **/
	FBoxSphereBounds HoudiniMeshSphereBounds;
	
	/** Original UClass value, before monkey patching. **/
	UClass* OriginalClass;

	/** Is set to true when this component is native and false is when it is dynamic. **/
	bool bIsNativeComponent;

	/** Is set to true if cooking job has been spawned for this component. **/
	bool bIsCooking;

	/** Holds this asset's handle. **/
	HAPI_AssetId AssetId;

	//
	UMaterial* Material;

private:

	int foo;
	//char buffer[65536];
	//__declspec(align(16)) char* buffer;
};
