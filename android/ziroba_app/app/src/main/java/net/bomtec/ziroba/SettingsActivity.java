package net.bomtec.ziroba;


import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;
import android.preference.PreferenceManager;


import net.bomtec.ziroba.R;

import java.util.List;



/**
 * A {@link PreferenceActivity} that presents a set of application settings. On
 * handset devices, settings are presented as a single list. On tablets,
 * settings are split by category, with category headers shown to the left of
 * the list of settings.
 * <p/>
 * See <a href="http://developer.android.com/design/patterns/settings.html">
 * Android Design: Settings</a> for design guidelines and the <a
 * href="http://developer.android.com/guide/topics/ui/settings.html">Settings
 * API Guide</a> for more information on developing a Settings UI.
 */
public class SettingsActivity extends PreferenceActivity {

    public static final String PREF_CONNECTION_KEY = "switch_connect";
    public static final String PREF_HOSTTEXT_KEY = "host_text";
    public static final String PREF_PORTTEXT_KEY = "port_text";
    public static final String PREF_SPEEDLIST_KEY = "speed_list";

    public static final String PREF_COMMAND_A_KEY = "a_command";
    public static final String PREF_COMMAND_UP_KEY = "up_command";
    public static final String PREF_COMMAND_B_KEY = "b_command";
    public static final String PREF_COMMAND_LEFT_KEY = "left_command";
    public static final String PREF_COMMAND_X_KEY = "x_command";
    public static final String PREF_COMMAND_RIGHT_KEY = "right_command";
    public static final String PREF_COMMAND_C_KEY = "c_command";
    public static final String PREF_COMMAND_DOWN_KEY = "down_command";
    public static final String PREF_COMMAND_D_KEY = "d_command";
    
    


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }


    @Override
    protected boolean isValidFragment(String fragmentName) {
        return  GeneralPrefFragment.class.getName().equals(fragmentName) ||
                CommandsPrefFragment.class.getName().equals(fragmentName);

    }



    /**
     * Populate the activity with the top-level headers.
     */
    @Override
    public void onBuildHeaders(List<Header> target) {
        loadHeadersFromResource(R.xml.pref_headers, target);
    }


    private static void updatePrefSummary(Preference pref, String key) {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(pref.getContext());
        if (pref instanceof EditTextPreference || pref instanceof  ListPreference) {
            pref.setSummary(sharedPreferences.getString(key, ""));
        }
    }


    /**
     * This fragment shows the preferences for the first header.
     */
    public static class GeneralPrefFragment extends PreferenceFragment
            implements SharedPreferences.OnSharedPreferenceChangeListener {

        @Override
        public void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);

            // Make sure default values are applied.  In a real app, you would
            // want this in a shared function that is used to retrieve the
            // SharedPreferences wherever they are needed.
            PreferenceManager.setDefaultValues(getActivity(),
                    R.xml.pref_general, false);

            addPreferencesFromResource(R.xml.pref_general);

            updateSummaries();
        }


        public void onSharedPreferenceChanged(SharedPreferences sharedPreferences,
                                              String key) {
            updateSummaries();
        }

        @Override
        public void onResume() {
            super.onResume();
            getPreferenceScreen().getSharedPreferences()
                    .registerOnSharedPreferenceChangeListener(this);

        }

        @Override
        public void onPause() {
            super.onPause();
            getPreferenceScreen().getSharedPreferences()
                    .unregisterOnSharedPreferenceChangeListener(this);
        }


        private void updateSummaries() {
            updatePrefSummary(findPreference(PREF_CONNECTION_KEY), PREF_CONNECTION_KEY);
            updatePrefSummary(findPreference(PREF_HOSTTEXT_KEY), PREF_HOSTTEXT_KEY);
            updatePrefSummary(findPreference(PREF_PORTTEXT_KEY), PREF_PORTTEXT_KEY);
            updatePrefSummary(findPreference(PREF_SPEEDLIST_KEY), PREF_SPEEDLIST_KEY);
        }

    }

    /**
     * This fragment shows the preferences for the second header.
     */
    public static class CommandsPrefFragment extends PreferenceFragment
            implements SharedPreferences.OnSharedPreferenceChangeListener {
        @Override
        public void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            // Make sure default values are applied.  In a real app, you would
            // want this in a shared function that is used to retrieve the
            // SharedPreferences wherever they are needed.
            PreferenceManager.setDefaultValues(getActivity(),
                    R.xml.pref_commands, false);

            // Load the preferences from an XML resource
            addPreferencesFromResource(R.xml.pref_commands);
            
            // Load and show default values
            updateSummaries();
        }
        public void onSharedPreferenceChanged(SharedPreferences sharedPreferences,
                                              String key) {
            updateSummaries();
        }

        @Override
        public void onResume() {
            super.onResume();
            getPreferenceScreen().getSharedPreferences()
                    .registerOnSharedPreferenceChangeListener(this);

        }

        @Override
        public void onPause() {
            super.onPause();
            getPreferenceScreen().getSharedPreferences()
                    .unregisterOnSharedPreferenceChangeListener(this);
        }


        private void updateSummaries() {
            updatePrefSummary(findPreference(PREF_COMMAND_A_KEY),PREF_COMMAND_A_KEY);
            updatePrefSummary(findPreference(PREF_COMMAND_UP_KEY), PREF_COMMAND_UP_KEY);
            updatePrefSummary(findPreference(PREF_COMMAND_B_KEY),PREF_COMMAND_B_KEY);
            updatePrefSummary(findPreference(PREF_COMMAND_LEFT_KEY), PREF_COMMAND_LEFT_KEY);
            updatePrefSummary(findPreference(PREF_COMMAND_X_KEY),PREF_COMMAND_X_KEY);
            updatePrefSummary(findPreference(PREF_COMMAND_RIGHT_KEY), PREF_COMMAND_RIGHT_KEY);
            updatePrefSummary(findPreference(PREF_COMMAND_C_KEY),PREF_COMMAND_C_KEY);
            updatePrefSummary(findPreference(PREF_COMMAND_DOWN_KEY), PREF_COMMAND_DOWN_KEY);
            updatePrefSummary(findPreference(PREF_COMMAND_D_KEY),PREF_COMMAND_D_KEY);
        }
        

    }

}

