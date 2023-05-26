#include "UpdateManager.h"
#include "ArmorRatingScaling.h"
#include "BashBlockStaminaPatch.h"
#include "Events.h"

namespace Hooks
{
	bool InstallHooks()
	{
		if (!UpdateManager::Install()) { return false; }
		if (!UpdateManager::InstallScalePatch()) { return false; }
		if (!UpdateManager::InstallFBlockPatch()) { return false; }
		if (!UpdateManager::InstallSpellCapPatch()) { return false; }
		
		WeaponFireHandler::InstallArrowReleaseHook();

		auto runtime = REL::Module::GetRuntime();
		if (Settings::GetSingleton()->armorScalingEnabled) {
			if (runtime == REL::Module::Runtime::AE) {
				ArmorRatingScaling::InstallArmorRatingHookAE();
			} else {
				ArmorRatingScaling::InstallArmorRatingHookSE();	
			}
		}

		if (!BashBlockStaminaPatch::InstallBlockMultHook()) {
			return false;
		}

		return true;
	}

	bool InstallBashMultHook() 
	{
		return BashBlockStaminaPatch::InstallBashMultHook();
	}
}
