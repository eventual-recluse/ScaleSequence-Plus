/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2020 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "DistrhoPlugin.hpp"
#include "ScaleSequencePlusControls.hpp"
#include "Tunings.h"
#include "libMTSMaster.cpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

/**
  Plugin to demonstrate File handling within DPF.
 */
class ScaleSequencePlus : public Plugin
{
public:
    ScaleSequencePlus()
        : Plugin(kParameterCount, 0, kStateCount),
          sampleRate(getSampleRate())
    {
        std::memset(fParameters, 0, sizeof(fParameters));
        
        // populate fParameters with defaults
        for (int32_t i = 0; i < kParameterCount; i++)
        {
            fParameters[i] = ParameterDefaults[i];
        }
        
        sampleRateChanged(sampleRate);
        
		current_scale = 0;
        tuning1 = Tunings::Tuning();
        tuning2 = Tunings::Tuning();
        tuning3 = Tunings::Tuning();
        tuning4 = Tunings::Tuning();
        tuning5 = Tunings::Tuning();
        tuning6 = Tunings::Tuning();
        tuning7 = Tunings::Tuning();
        tuning8 = Tunings::Tuning();
        
        //Fill frequency arrays with default frequencies from tuning1
        
        for (int32_t i = 0; i < 128; i++)
        {
            frequencies_in_hz[i] = tuning1.frequencyForMidiNote(i);;
            target_frequencies_in_hz[i] = tuning1.frequencyForMidiNote(i);;
        }
    }

protected:
   /* --------------------------------------------------------------------------------------------------------
    * Information */

   /**
      Get the plugin label.
      This label is a short restricted name consisting of only _, a-z, A-Z and 0-9 characters.
    */
    const char* getLabel() const override
    {
        return "ScaleSequence-Plus";
    }

   /**
      Get an extensive comment/description about the plugin.
    */
    const char* getDescription() const override
    {
        return "MTS-ESP Scale Sequencer.";
    }

   /**
      Get the plugin author/maker.
    */
    const char* getMaker() const override
    {
        return "eventual-recluse";
    }

   /**
      Get the plugin homepage.
    */
    const char* getHomePage() const override
    {
        return "https://github.com/eventual-recluse/ScaleSequence-Plus";
    }

   /**
      Get the plugin license name (a single line of text).
      For commercial plugins this should return some short copyright information.
    */
    const char* getLicense() const override
    {
        return "GPL3";
    }

   /**
      Get the plugin version, in hexadecimal.
    */
    uint32_t getVersion() const override
    {
        return d_version(0, 0, 0);
    }

   /**
      Get the plugin unique Id.
      This value is used by LADSPA, DSSI and VST plugin formats.
    */
    int64_t getUniqueId() const override
    {
        return d_cconst('S', 'c', 'l', 'P');
    }

   /* --------------------------------------------------------------------------------------------------------
    * Init */

   /**
      Initialize the audio port @a index.@n
      This function will be called once, shortly after the plugin is created.
    */
    void initAudioPort(bool input, uint32_t index, AudioPort& port) override
    {
        // treat meter audio ports as stereo
        port.groupId = kPortGroupMono;

        // everything else is as default
        Plugin::initAudioPort(input, index, port);
    }

   /**
      Initialize the parameter @a index.
      This function will be called once, shortly after the plugin is created.
    */
    void initParameter(uint32_t index, Parameter& parameter) override
    {
        
        switch (index)
        {
        case kParameterMeasure:
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.name   = "Measure";
            parameter.symbol = "measure";
            parameter.enumValues.count = 3;
            parameter.enumValues.restrictedMode = true;
            {
                ParameterEnumerationValue* const values = new ParameterEnumerationValue[3];
                parameter.enumValues.values = values;

                values[0].label = "Beats";
                values[0].value = 0;
                values[1].label = "Bars";
                values[1].value = 1;
                values[2].label = "MIDI Note";
                values[2].value = 2;
            }
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterMultiplier:
            parameter.name = "Multiplier";
            parameter.symbol = "multiplier";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterScaleGlide:
            parameter.name = "Scale Glide";
            parameter.symbol = "scaleGlide";
            parameter.hints = kParameterIsAutomatable|kParameterIsLogarithmic;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep1:
            parameter.name = "Step 1";
            parameter.symbol = "step1";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep2:
            parameter.name = "Step 2";
            parameter.symbol = "step2";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep3:
            parameter.name = "Step 3";
            parameter.symbol = "step3";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep4:
            parameter.name = "Step 4";
            parameter.symbol = "step4";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep5:
            parameter.name = "Step 5";
            parameter.symbol = "step5";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep6:
            parameter.name = "Step 6";
            parameter.symbol = "step6";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep7:
            parameter.name = "Step 7";
            parameter.symbol = "step7";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep8:
            parameter.name = "Step 8";
            parameter.symbol = "step8";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep9:
            parameter.name = "Step 9";
            parameter.symbol = "step9";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep10:
            parameter.name = "Step 10";
            parameter.symbol = "step10";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep11:
            parameter.name = "Step 11";
            parameter.symbol = "step11";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep12:
            parameter.name = "Step 12";
            parameter.symbol = "step12";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep13:
            parameter.name = "Step 13";
            parameter.symbol = "step13";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep14:
            parameter.name = "Step 14";
            parameter.symbol = "step14";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep15:
            parameter.name = "Step 15";
            parameter.symbol = "step15";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep16:
            parameter.name = "Step 16";
            parameter.symbol = "step16";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep17:
            parameter.name = "Step 17";
            parameter.symbol = "step17";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep18:
            parameter.name = "Step 18";
            parameter.symbol = "step18";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep19:
            parameter.name = "Step 19";
            parameter.symbol = "step19";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep20:
            parameter.name = "Step 20";
            parameter.symbol = "step20";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep21:
            parameter.name = "Step 21";
            parameter.symbol = "step21";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep22:
            parameter.name = "Step 22";
            parameter.symbol = "step22";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep23:
            parameter.name = "Step 23";
            parameter.symbol = "step23";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep24:
            parameter.name = "Step 24";
            parameter.symbol = "step24";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep25:
            parameter.name = "Step 25";
            parameter.symbol = "step25";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep26:
            parameter.name = "Step 26";
            parameter.symbol = "step26";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep27:
            parameter.name = "Step 27";
            parameter.symbol = "step27";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep28:
            parameter.name = "Step 28";
            parameter.symbol = "step28";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep29:
            parameter.name = "Step 29";
            parameter.symbol = "step29";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep30:
            parameter.name = "Step 30";
            parameter.symbol = "step30";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep31:
            parameter.name = "Step 31";
            parameter.symbol = "step31";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterStep32:
            parameter.name = "Step 32";
            parameter.symbol = "step32";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterOffset:
            parameter.name = "Offset";
            parameter.symbol = "offset";
            parameter.hints = kParameterIsAutomatable;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
		case kParameterLoopPoint:
            parameter.name = "Loop Point";
            parameter.symbol = "looppoint";
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger;
            parameter.ranges.min = controlLimits[index].first;
            parameter.ranges.max = controlLimits[index].second;
            parameter.ranges.def = ParameterDefaults[index];
            break;
        case kParameterCurrentStep:
			parameter.name = "Current Step";
            parameter.symbol = "currentstep";
            parameter.hints = kParameterIsOutput;
			break;
        }
    }

   /**
      Initialize the state @a index.@n
      This function will be called once, shortly after the plugin is created.
    */
    void initState(uint32_t index, State& state) override
    {
        switch (index)
        {
        case kStateFileSCL1:
            state.key = "scl_file_1";
            state.label = "SCL File 1";
            break;
        case kStateFileSCL2:
            state.key = "scl_file_2";
            state.label = "SCL File 2";
            break;
        case kStateFileSCL3:
            state.key = "scl_file_3";
            state.label = "SCL File 3";
            break;
        case kStateFileSCL4:
            state.key = "scl_file_4";
            state.label = "SCL File 4";
            break;
        case kStateFileSCL5:
            state.key = "scl_file_5";
            state.label = "SCL File 5";
            break;
        case kStateFileSCL6:
            state.key = "scl_file_6";
            state.label = "SCL File 6";
            break;
        case kStateFileSCL7:
            state.key = "scl_file_7";
            state.label = "SCL File 7";
            break;
        case kStateFileSCL8:
            state.key = "scl_file_8";
            state.label = "SCL File 8";
            break;
        case kStateFileKBM1:
            state.key = "kbm_file_1";
            state.label = "KBM File 1";
            break;
        case kStateFileKBM2:
            state.key = "kbm_file_2";
            state.label = "KBM File 2";
            break;
        case kStateFileKBM3:
            state.key = "kbm_file_3";
            state.label = "KBM File 3";
            break;
        case kStateFileKBM4:
            state.key = "kbm_file_4";
            state.label = "KBM File 4";
            break;
        case kStateFileKBM5:
            state.key = "kbm_file_5";
            state.label = "KBM File 5";
            break;
        case kStateFileKBM6:
            state.key = "kbm_file_6";
            state.label = "KBM File 6";
            break;
        case kStateFileKBM7:
            state.key = "kbm_file_7";
            state.label = "KBM File 7";
            break;
        case kStateFileKBM8:
            state.key = "kbm_file_8";
            state.label = "KBM File 8";
            break;
        }

        state.hints = kStateIsFilenamePath;
    }

   /* --------------------------------------------------------------------------------------------------------
    * Internal data */

   /**
      Get the current value of a parameter.
      The host may call this function from any context, including realtime processing.
    */
    float getParameterValue(uint32_t index) const override
    {
        return fParameters[index];
    }

   /**
      Change a parameter value.@n
      The host may call this function from any context, including realtime processing.

      This function will only be called for parameter inputs.
    */
    void setParameterValue(uint32_t index, float value) override
    {
		fParameters[index] = value;
	}

   /**
      Change an internal state @a key to @a value.
    */
    void setState(const char* key, const char* value) override
    {
		// note: internal states seem to get set as soon as file chosen by file dialog, and could end up being anything
		
        //d_stdout("DSP setState %s %s", key, value);
        int fileId = -1;

        /**/ if (std::strcmp(key, "scl_file_1") == 0)
        {
		    fileId = 0;
		}
        else if (std::strcmp(key, "scl_file_2") == 0)
        {   
			fileId = 1;
		}
        else if (std::strcmp(key, "scl_file_3") == 0)
	    {
            fileId = 2;
        }
        else if (std::strcmp(key, "scl_file_4") == 0)
	    {
            fileId = 3;
        }
        else if (std::strcmp(key, "scl_file_5") == 0)
        {
		    fileId = 4;
		}
        else if (std::strcmp(key, "scl_file_6") == 0)
        {   
			fileId = 5;
		}
        else if (std::strcmp(key, "scl_file_7") == 0)
	    {
            fileId = 6;
        }
        else if (std::strcmp(key, "scl_file_8") == 0)
	    {
            fileId = 7;
        }
        else if (std::strcmp(key, "kbm_file_1") == 0)
	    {
            fileId = 8;
        }
        else if (std::strcmp(key, "kbm_file_2") == 0)
	    {
            fileId = 9;
        }
        else if (std::strcmp(key, "kbm_file_3") == 0)
	    {
            fileId = 10;
        }
        else if (std::strcmp(key, "kbm_file_4") == 0)
	    {
            fileId = 11;
        }
        else if (std::strcmp(key, "kbm_file_5") == 0)
	    {
            fileId = 12;
        }
        else if (std::strcmp(key, "kbm_file_6") == 0)
	    {
            fileId = 13;
        }
        else if (std::strcmp(key, "kbm_file_7") == 0)
	    {
            fileId = 14;
        }
        else if (std::strcmp(key, "kbm_file_8") == 0)
	    {
            fileId = 15;
        }
        
        if (fileId == -1)
            return;

        if (FILE* const fh = fopen(value, "r"))
        {
			
			if (!value)
			{    
			    fclose(fh);
			    return; 
			}
			
			//d_stdout(value);
			
			//String filename(value);
			

			if (fileId == 0)
			{	
				loadScl(tuning1, value);
			}
			else if (fileId == 1)
			{
				loadScl(tuning2, value);
			}
			else if (fileId == 2)
			{
				loadScl(tuning3, value);
			}	
			else if (fileId == 3)
			{	
				loadScl(tuning4, value);
			}
			else if (fileId == 4)
			{	
				loadScl(tuning5, value);
			}
			else if (fileId == 5)
			{
				loadScl(tuning6, value);
			}
			else if (fileId == 6)
			{
				loadScl(tuning7, value);
			}	
			else if (fileId == 7)
			{	
				loadScl(tuning8, value);
			}				
			else if (fileId == 8)
			{
				loadKbm(tuning1, value);
			}
			else if (fileId == 9)
			{
				loadKbm(tuning2, value);
			}
			else if (fileId == 10)
			{
				loadKbm(tuning3, value);
			}
			else if (fileId == 11)
			{
				loadKbm(tuning4, value);
			}
			else if (fileId == 12)
			{
				loadKbm(tuning5, value);
			}
			else if (fileId == 13)
			{
				loadKbm(tuning6, value);
			}
			else if (fileId == 14)
			{
				loadKbm(tuning7, value);
			}
			else if (fileId == 15)
			{
				loadKbm(tuning8, value);
			}
			
            fclose(fh);
        }
    }
    
    void loadScl(Tunings::Tuning & tn, const char* value)
    {
		String filename(value);
		auto k = tn.keyboardMapping;
		
		if (filename.endsWith(".scl"))
		{
			try
			{   auto s = Tunings::readSCLFile(value);
				tn = Tunings::Tuning(s, k);
				//d_stdout("ScaleSequence-Plus: tuning set to %s", value);
			}
			catch (const std::exception& e)
			{
				tn = Tunings::Tuning();
				d_stdout("ScaleSequence-Plus:Exception when setting tuning");
				d_stdout(e.what());
			}
		}
		else
		{
			auto s = Tunings::Tuning().scale;
			tn = Tunings::Tuning(s, k);
			//d_stdout("ScaleSequence-Plus: tuning scl reset");
		}
	}
	
	void loadKbm(Tunings::Tuning & tn, const char* value)
	{
		String filename(value);
		auto s = tn.scale;
		if (filename.endsWith(".kbm"))
		{
			try
			{
				auto k = Tunings::readKBMFile(value);
				tn = Tunings::Tuning(s, k);
				//d_stdout("ScaleSequence-Plus: tuning set to %s", value);
			}
			catch (const std::exception& e)
			{
				tn = Tunings::Tuning();
				d_stdout("ScaleSequence-Plus:Exception when setting tuning");
				d_stdout(e.what());
			}
		}
		else
		{
			auto k = Tunings::Tuning().keyboardMapping;
			tn = Tunings::Tuning(s, k);
			//d_stdout("ScaleSequence-Plus: tuning kbm reset");
		}
	}

    /* --------------------------------------------------------------------------------------------------------
    * Activate / Deactivate */
    
    void activate() override
    {
	    if (MTS_CanRegisterMaster())
			MTS_RegisterMaster();
		current_scale = 0;
	}
	
    void deactivate() override
    {
        MTS_DeregisterMaster();
    }
    
   /* --------------------------------------------------------------------------------------------------------
    * Audio/MIDI Processing */

   /**
      Run/process function for plugins with MIDI input.
      @note Some parameters might be null if there are no audio inputs or outputs.
    */
    void run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount) override
    {
		int32_t stepIndex = static_cast<int32_t>(fParameters[kParameterCurrentStep] / 0.03125f) -1;
        int32_t loopPoint = static_cast<int32_t>(fParameters[kParameterLoopPoint]);
        
        // Loop through the MIDI events. We do this whatever the setting, as we will pass them all through to MIDI out
		for (uint32_t currentMidiEvent = 0; currentMidiEvent < midiEventCount; ++currentMidiEvent)
		{
		     if (midiEvents[currentMidiEvent].size <= 3)
		     {   uint8_t data0 = midiEvents[currentMidiEvent].data[0];
	             if ( ((data0 & 0xF0) == 0x90) and (fParameters[kParameterMeasure] == 2) ) // Received a Note on, and using MIDI note on to advance step
                     stepIndex = (stepIndex + 1) % loopPoint;
			 }
			 // Pass all MIDI events through
			 writeMidiEvent(midiEvents[currentMidiEvent]);
		}
        
		if (fParameters[kParameterMeasure] != 2) // Using beats or bars to find step position
		{
			stepIndex = 0;
            const TimePosition& timePos(getTimePosition());
        
            double beats_per_bar = timePos.bbt.beatsPerBar;
            // In DISTRHO DPF, the first bar == 1. But our calculations require first bar == 0
            double bar = timePos.bbt.bar - 1;
            // In DISTRHO DPF, the first beat of the bar == 1. Our calculations require first beat of the bar == 0
            double beat = timePos.bbt.beat - 1;
            double beatFraction   = timePos.bbt.tick / timePos.bbt.ticksPerBeat;
            double beatsFromStart = (bar * beats_per_bar) + beat + beatFraction;
                
            // Offset. Might cause weirdness at the start of the track. But stepIndex below should be ignored if less than zero.
            if (fParameters[kParameterMeasure] == 0) // using beats
                beatsFromStart -= fParameters[kParameterOffset];
            else if (fParameters[kParameterMeasure] == 1) //using bars
                bar -= fParameters[kParameterOffset];
        
            // Which step are we on?
            if (fParameters[kParameterMeasure] == 0) // using beats
                stepIndex = static_cast<int32_t>(std::floor(beatsFromStart / fParameters[kParameterMultiplier])) % loopPoint;
            else if (fParameters[kParameterMeasure] == 1) // using bars
                stepIndex = static_cast<int32_t>(std::floor(bar / fParameters[kParameterMultiplier])) % loopPoint;
		}
        
        // Set current step parameter for UI feedback
        fParameters[kParameterCurrentStep] = static_cast<float>((stepIndex + 1) * 0.03125f);
        
        int32_t stepScale = 0;
        
        // What should the scale be for this step?
        switch (stepIndex)
        {
        case 0:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep1]);
            break;
        case 1:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep2]);
            break;
        case 2:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep3]);
            break;
        case 3:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep4]);
            break;
        case 4:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep5]);
            break;
        case 5:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep6]);
            break;
        case 6:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep7]);
            break;
        case 7:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep8]);
            break;
        case 8:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep9]);
            break;
        case 9:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep10]);
            break;
        case 10:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep11]);
            break;
        case 11:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep12]);
            break;
        case 12:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep13]);
            break;
        case 13:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep14]);
            break;
        case 14:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep15]);
            break;
        case 15:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep16]);
            break;
        case 16:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep17]);
            break;
        case 17:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep18]);
            break;
        case 18:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep19]);
            break;
        case 19:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep20]);
            break;
        case 20:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep21]);
            break;
        case 21:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep22]);
            break;
        case 22:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep23]);
            break;
        case 23:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep24]);
            break;
        case 24:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep25]);
            break;
        case 25:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep26]);
            break;
        case 26:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep27]);
            break;
        case 27:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep28]);
            break;
        case 28:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep29]);
            break;
        case 29:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep30]);
            break;
        case 30:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep31]);
            break;
        case 31:
            stepScale = static_cast<uint32_t>(fParameters[kParameterStep32]);
            break;
        default:
            break;
		}
		
		// Switch scale if necessary
		// if stepScale is still 0 it will be ignored, and the tuning won't change
        if (stepScale != current_scale)
        {
			switch (stepScale)
			{
			case 1:
			{
				for (int32_t i = 0; i < 128; i++)
				{
					target_frequencies_in_hz[i] = tuning1.frequencyForMidiNote(i);
				}
				break;
			}
			case 2:
			{
				for (int32_t i = 0; i < 128; i++)
				{
					target_frequencies_in_hz[i] = tuning2.frequencyForMidiNote(i);
				}
				break;
			}
			case 3:
			{
				for (int32_t i = 0; i < 128; i++)
				{
					target_frequencies_in_hz[i] = tuning3.frequencyForMidiNote(i);
				}
				break;
			}
			case 4:
			{
				for (int32_t i = 0; i < 128; i++)
				{
					target_frequencies_in_hz[i] = tuning4.frequencyForMidiNote(i);
				}
				break;
			}
			case 5:
			{
				for (int32_t i = 0; i < 128; i++)
				{
					target_frequencies_in_hz[i] = tuning5.frequencyForMidiNote(i);
				}
				break;
			}
			case 6:
			{
				for (int32_t i = 0; i < 128; i++)
				{
					target_frequencies_in_hz[i] = tuning6.frequencyForMidiNote(i);
				}
				break;
			}
			case 7:
			{
				for (int32_t i = 0; i < 128; i++)
				{
					target_frequencies_in_hz[i] = tuning7.frequencyForMidiNote(i);
				}
				break;
			}
			case 8:
			{
				for (int32_t i = 0; i < 128; i++)
				{
					target_frequencies_in_hz[i] = tuning8.frequencyForMidiNote(i);
				}
				break;
			}
			default:
                break;
			}
	
		}
		
		// Scale glide, continuous tuning. Currently done via division of the remaining difference to target
		// for every frame
	        for (uint32_t fr = 0; fr < frames; ++fr)
		{
			for (int32_t i = 0; i < 128; i++)
			{
				double difference = target_frequencies_in_hz[i] - frequencies_in_hz[i];
				if (std::fabs(difference) < 0.0001f)
					frequencies_in_hz[i] = target_frequencies_in_hz[i];
				else
					frequencies_in_hz[i] = frequencies_in_hz[i] + (difference / (fParameters[kParameterScaleGlide] * 1000.0));
			}
			// Set MTS-ESP Scale
			MTS_SetNoteTunings(frequencies_in_hz);
		}
    }
    

    // -------------------------------------------------------------------------------------------------------

private:
    float sampleRate;

    float fParameters[kParameterCount];
    Tunings::Tuning tuning1, tuning2, tuning3, tuning4,
                    tuning5, tuning6, tuning7, tuning8;
    
    double frequencies_in_hz[128];
    double target_frequencies_in_hz[128];
    uint32_t current_scale;

   /**
      Set our plugin class as non-copyable and add a leak detector just in case.
    */
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScaleSequencePlus)
};

/* ------------------------------------------------------------------------------------------------------------
 * Plugin entry point, called by DPF to create a new plugin instance. */

Plugin* createPlugin()
{
    return new ScaleSequencePlus();
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
