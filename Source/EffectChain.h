/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
//
//  EffectChain.h
//  modularSynth
//
//  Created by Ryan Challinor on 11/25/12.
//
//

#ifndef __modularSynth__EffectChain__
#define __modularSynth__EffectChain__

#include <iostream>
#include "IAudioProcessor.h"
#include "IDrawableModule.h"
#include "ClickButton.h"
#include "Slider.h"
#include "Checkbox.h"
#include "DropdownList.h"

#define MAX_EFFECTS_IN_CHAIN 100
#define MIN_EFFECT_WIDTH 80

class IAudioEffect;

class EffectChain : public IDrawableModule, public IAudioProcessor, public IButtonListener, public IFloatSliderListener, public IDropdownListener
{
public:
   EffectChain();
   virtual ~EffectChain();
   static IDrawableModule* Create() { return new EffectChain(); }
   
   
   void CreateUIControls() override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   
   void Init() override;
   void Poll() override;
   void AddEffect(std::string type, bool onTheFly = false);
   void SetWideCount(int count) { mNumFXWide = count; }
   
   //IAudioSource
   void Process(double time) override;
   
   void KeyPressed(int key, bool isRepeat) override;
   void KeyReleased(int key) override;

   bool HasPush2OverrideControls() const override { return true; }
   void GetPush2OverrideControls(std::vector<IUIControl*>& controls) const override;

   void ButtonClicked(ClickButton* button) override;
   void CheckboxUpdated(Checkbox* checkbox) override;
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override;
   void DropdownUpdated(DropdownList* list, int oldVal) override;
   
   virtual void LoadBasics(const ofxJSONElement& moduleInfo, std::string typeName) override;
   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;
   virtual void SaveLayout(ofxJSONElement& moduleInfo) override;
   virtual void UpdateOldControlName(std::string& oldName) override;
   
private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& width, float& height) override;
   bool Enabled() const override { return mEnabled; }
   std::vector<IUIControl*> ControlsToIgnoreInSaveState() const override;
   
   int GetRowHeight(int row) const;
   int NumRows() const;
   void DeleteEffect(int index);
   void MoveEffect(int index, int direction);
   void UpdateReshuffledDryWetSliders();
   ofVec2f GetEffectPos(int index) const;

   struct EffectControls
   {
      ClickButton* mMoveLeftButton;
      ClickButton* mMoveRightButton;
      ClickButton* mDeleteButton;
      FloatSlider* mDryWetSlider;
      ClickButton* mPush2DisplayEffectButton;
   };
   
   std::vector<IAudioEffect*> mEffects;
   ChannelBuffer mDryBuffer;
   std::vector<EffectControls> mEffectControls;
   std::array<float, MAX_EFFECTS_IN_CHAIN> mDryWetLevels;
   
   double mSwapTime;
   int mSwapFromIdx;
   int mSwapToIdx;
   ofVec2f mSwapFromPos;
   ofVec2f mSwapToPos;
   float mVolume;
   FloatSlider* mVolumeSlider;
   int mNumFXWide;
   bool mInitialized;
   bool mShowSpawnList;
   int mWantToDeleteEffectAtIndex;
   IAudioEffect* mPush2DisplayEffect;
   
   std::vector<std::string> mEffectTypesToSpawn;
   int mSpawnIndex;
   DropdownList* mEffectSpawnList;
   ClickButton* mSpawnEffectButton;
   ClickButton* mPush2ExitEffectButton;
   
   ofMutex mEffectMutex;
};

#endif /* defined(__modularSynth__EffectChain__) */
