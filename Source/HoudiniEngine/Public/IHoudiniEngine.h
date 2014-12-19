/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * Produced by:
 *      Damian Campeanu, Mykola Konyk
 *      Side Effects Software Inc
 *      123 Front Street West, Suite 1401
 *      Toronto, Ontario
 *      Canada   M5J 2M2
 *      416-504-9876
 *
 */

#pragma once

class UStaticMesh;
class ISlateStyle;
struct FHoudiniEngineNotificationInfo;
struct FHoudiniEngineTask;

class IHoudiniEngine : public IModuleInterface
{
public:

	/** Register component visualizers used by this module. **/
	virtual void RegisterComponentVisualizers() {}

	/** Unregister components visualizers used by this module. **/
	virtual void UnregisterComponentVisualizers() {}

	/** Return static mesh reprensenting Houdini logo. **/
	virtual UStaticMesh* GetHoudiniLogoStaticMesh() const = 0;

	/** Return true if HAPI version mismatch is detected (between defined and running versions). **/
	virtual bool CheckHapiVersionMismatch() const = 0;

	/** Return Houdini logo brush. **/
	virtual TSharedPtr<FSlateDynamicImageBrush> GetHoudiniLogoBrush() const = 0;

	/** Return Slate style set. **/
	virtual TSharedPtr<ISlateStyle> GetSlateStyle() const = 0;

	/** Register task for execution. **/
	virtual void AddTask(const FHoudiniEngineTask& Task) = 0;

	/** Register task info. **/
	virtual void AddTaskInfo(const FGuid HapIGUID, const FHoudiniEngineTaskInfo& TaskInfo) = 0;

	/** Remove task info. **/
	virtual void RemoveTaskInfo(const FGuid HapIGUID) = 0;

	/** Retrieve task info. **/
	virtual bool RetrieveTaskInfo(const FGuid HapIGUID, FHoudiniEngineTaskInfo& TaskInfo) = 0;
};
