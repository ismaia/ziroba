package net.bomtec.ziroba;


import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;
import android.preference.PreferenceManager;
import android.preference.SwitchPreference;


import java.util.List;



/**
 * A PreferenceActivity that presents a set of application settings.
 * @author Isaac Maia
 */
public class SettingsActivity extends PreferenceActivity {

    public static final String PREF_KEY_SW_CONNECTION = "switch_connect";
    public static final String PREF_KEY_HOST_TEXT     = "host_text";
    public static final String PREF_KEY_PORT_TEXT     = "port_text";
    public static final String PREF_KEY_SPEED_LIST    = "speed_list";
    public static final String PREF_KEY_DEFAULT       = "pref_default_values";

    public static final String PREF_KEY_COMMAND_A     = "a_command";
    public static final String PREF_KEY_COMMAND_B     = "b_command";
    public static final String PREF_KEY_COMMAND_C     = "c_command";
    public static final String PREF_KEY_COMMAND_D     = "d_command";
    public static final String PREF_KEY_COMMAND_E     = "e_command";
    public static final String PREF_KEY_COMMAND_F     = "f_command";
    public static final String PREF_KEY_COMMAND_G     = "g_command";
    public static final String PREF_KEY_COMMAND_H     = "h_command";


    public static SharedPreferences sharedPreferences;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        sharedPreferences =   PreferenceManager.getDefaultSharedPreferences(this);

    }


    @Override
    protected boolean isValidFragment(String fragmentName) {
        return  GeneralPrefFragment.class.getName().equals(fragmentName) ||
                CommandsPrefFragment.class.getName().equals(fragmentName);

    }


    /**
     * Populates the activity with the top-level headers.
     */
    @Override
    public void onBuildHeaders(List<Header> target) {
        loadHeadersFromResource(R.xml.pref_headers, target);
    }


    /**
     * Updates summaries with their new values
     * @param pref
     */
    private static void updatePrefSummary(Preference pref) {
        if (pref instanceof EditTextPreference) {
            EditTextPreference editTextPref = (EditTextPreference)pref;
            pref.setSummary(editTextPref.getText());
        }else if (pref instanceof ListPreference) {
            ListPreference listPref = (ListPreference) pref;
            pref.setSummary(listPref.getEntry());
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


            Preference pref = (Preference) findPreference(PREF_KEY_DEFAULT);
            pref.setOnPreferenceClickListener(new Preference.OnPreferenceClickListener() {
                public boolean onPreferenceClick(Preference preference) {
                    //open browser or intent here
                    AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
                    builder.setTitle("Reset Values");
                    builder.setMessage("Do you want to reset all values?");
                    builder.setCancelable(true);
                    builder.setPositiveButton(
                            "Yes", new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int id) {
                                    SharedPreferences.Editor editor = sharedPreferences.edit();
                                    editor.clear();
                                    editor.commit();
                                }
                            });
                    builder.setNegativeButton("No", new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int id) {
                            dialog.cancel();
                        }
                    });
                    builder.create();
                    builder.show();
                    return true;
                }
            });

            //sets the right value to the connection switch
            SwitchPreference sw = (SwitchPreference)findPreference(PREF_KEY_SW_CONNECTION);
            //sw.setChecked(CmdClient.getInstance().isActive());
            sw.setChecked(ZirobaRobot.getInstance().isActive());

            updateSummaries();
        }


        public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {


            if (key.equals(PREF_KEY_SW_CONNECTION) ||
                    key.equals(PREF_KEY_HOST_TEXT)  ||
                    key.equals(PREF_KEY_PORT_TEXT)) {

                String host = sharedPreferences.getString(PREF_KEY_HOST_TEXT, "");
                String port = sharedPreferences.getString(PREF_KEY_PORT_TEXT, "");

                boolean swState = sharedPreferences.getBoolean(PREF_KEY_SW_CONNECTION, false);
                SwitchPreference sw = (SwitchPreference)findPreference(PREF_KEY_SW_CONNECTION);

                boolean connState = false;
                if (swState) {
                    connState = ZirobaRobot.getInstance().connect(getActivity(),host,port);
                }else {
                    //close client socket
                    ZirobaRobot.getInstance().stop();
                }

                //update the sw state
                sw.setChecked(connState);
            }

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
            updatePrefSummary(findPreference(PREF_KEY_SW_CONNECTION));
            updatePrefSummary(findPreference(PREF_KEY_HOST_TEXT));
            updatePrefSummary(findPreference(PREF_KEY_PORT_TEXT));
            updatePrefSummary(findPreference(PREF_KEY_SPEED_LIST));
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
                    R.xml.pref_buttons, false);

            // Load the preferences from an XML resource
            addPreferencesFromResource(R.xml.pref_buttons);

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
            updatePrefSummary(findPreference(PREF_KEY_COMMAND_A));
            updatePrefSummary(findPreference(PREF_KEY_COMMAND_B));
            updatePrefSummary(findPreference(PREF_KEY_COMMAND_C));
            updatePrefSummary(findPreference(PREF_KEY_COMMAND_D));
            updatePrefSummary(findPreference(PREF_KEY_COMMAND_E));
            updatePrefSummary(findPreference(PREF_KEY_COMMAND_F));
            updatePrefSummary(findPreference(PREF_KEY_COMMAND_G));
            updatePrefSummary(findPreference(PREF_KEY_COMMAND_H));


        }
    }


}

