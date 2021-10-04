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
//  EQEffect.h
//  Bespoke
//
//  Created by Ryan Challinor on 12/26/14.
//
//

#ifndef __Bespoke__EQEffect__
#define __Bespoke__EQEffect__

#include "IAudioEffect.h"
#include "DropdownList.h"
#include "Checkbox.h"
#include "Slider.h"
#include "Transport.h"
#include "BiquadFilter.h"
#include "RadioButton.h"
#include "UIGrid.h"
#include "ClickButton.h"

#define NUM_EQ_FILTERS 8

class EQEffect : public IAudioEffect, public IDropdownListener, public IIntSliderListener, public IRadioButtonListener, public IButtonListener, public UIGridListener
{
public:
   EQEffect();
   ~EQEffect();
   
   static IAudioEffect* Create() { return new EQEffect(); }
   
   std::string GetTitleLabel() override { return "basiceq"; }
   void CreateUIControls() override;
   
   void Init() override;
   
   //IAudioEffect
   void ProcessAudio(double time, ChannelBuffer* buffer) override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   float GetEffectAmount() override;
   std::string GetType() override { return "basiceq"; }
   
   void DropdownUpdated(DropdownList* list, int oldVal) override;
   void CheckboxUpdated(Checkbox* checkbox) override;
   void IntSliderUpdated(IntSlider* slider, int oldVal) override;
   void RadioButtonUpdated(RadioButton* list, int oldVal) override;
   void ButtonClicked(ClickButton* button) override;
   void GridUpdated(UIGrid* grid, int col, int row, float value, float oldValue) override;
   
private:
   //IDrawableModule
   void GetModuleDimensions(float& width, float& height) override;
   void DrawModule() override;
   bool Enabled() const override { return mEnabled; }

   struct FilterBank
   {
      BiquadFilter mBiquad[NUM_EQ_FILTERS];
   };
   
   FilterBank mBanks[ChannelBuffer::kMaxNumChannels];
   int mNumFilters;
   
   UIGrid* mMultiSlider;
   ClickButton* mEvenButton;
};

#endif /* defined(__Bespoke__EQEffect__) */
