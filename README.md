# ScaleSequence Plus

ScaleSequence Plus is a prototype [MTS-ESP](https://github.com/ODDSound/MTS-ESP) master plugin, which allows the dynamic switching of the current scale according to a set sequence.

![ScaleSequence Plus](https://raw.githubusercontent.com/eventual-recluse/ScaleSequence-Plus/main/plugins/ScaleSequencePlus/ScaleSequencePlus_screenshot.png "ScaleSequence Plus")<br/>

# Settings

Each of the eight scales can be set by loading a either a Scala scale file (.scl), keymapping file (.kbm) file, or both. Click "Open SCL File" or "Open KBM File" to choose the file.

The sequence has 32 steps. Set the scale for each step by clicking the sequence buttons.

More parameters:

**Step Multi:** Multiplies the length of the step. e.g. if the step type is beats, setting Step Multi to 2 will set each step to 2 beats. (Step Multi is ignored if the Step Type is set to MIDI Note.)<br>
**Step Type:** The options are beats, bars or MIDI Note. If MIDI Note is chosen, the step advances every time a MIDI Note is received.<br>
**Glide:** The glide amount for smoothly switching between scales. The higher the glide amount, the longer it will take to switch completely.<br>
**Offset:** This setting allows the timing of the scale switching be moved a little earlier or later. Up to -1 or +1 beat or bar (depending on the step type chosen). (Offset is ignored if the Step Type is set to MIDI Note.)<br>
**Loop Point:** Sets the step at which the sequence loops back to the start.

# Notes

To use these plugins, you will need Scala scale files (.scl) and / or keymapping files (.kbm). You will also need to install [libMTS.](https://github.com/ODDSound/MTS-ESP)

There is a large collection of .scl files at the [Scala Scale Archive.](https://huygens-fokker.org/microtonality/scales.html)

A collection of .scl and .kbm files can be found in the [Sevish Tuning Pack.](https://sevish.com/music-resources/#tuning-files)

# Credits
[DISTRHO Plugin Framework.](https://github.com/DISTRHO/DPF) ISC license.

[MTS-ESP.](https://github.com/ODDSound/MTS-ESP) 0BSD license.

[Surge Synthesizer Tuning Library.](https://github.com/surge-synthesizer/tuning-library) MIT license.

[Dear ImGui.](https://github.com/ocornut/imgui) MIT license.

[Bruno Ace Font](https://fonts.google.com/specimen/Bruno+Ace) designed by Astigmatic. [Open Font License.](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL)

[Bruno Ace SC Font](https://fonts.google.com/specimen/Bruno+Ace+SC) designed by Astigmatic. [Open Font License.](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL)

[Lekton Font](https://fonts.google.com/specimen/Lekton) designed by ISIA Urbino. [Open Font License.](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL)
