using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NAudio.CoreAudioApi;
using System.IO.Ports;

namespace RGB_controll
{

    // quality range 0 to 65
    // normal  range 0 to 50
    public partial class Form1 : Form
    {
        const int maximumPeak = 50;

        public SerialPort port = new SerialPort("COM7", 9600);
        public Form1()
        {
            InitializeComponent();
            MMDeviceEnumerator enumerator = new MMDeviceEnumerator();
            var devices = enumerator.EnumerateAudioEndPoints(DataFlow.All, DeviceState.Active);
            comboBox1.Items.AddRange(devices.ToArray());
            
            port.Open();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            if (comboBox1.SelectedItem != null)
            {
                var device = (MMDevice)comboBox1.SelectedItem;
                int level = (int)(Math.Round(device.AudioMeterInformation.MasterPeakValue * 100));
                sendSerial(level);
            }
        }

        private static int remap(int value, int fromLow, int fromHigh, int toLow, int toHigh)
        {
            return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
        }

        public void sendSerial(int level) {

            if (level > maximumPeak) level = maximumPeak;
            port.Write(remap(level, 0, 50, 0, 255).ToString());

        }

        private void button1_Click(object sender, EventArgs e)
        {
            port.Close();
        }
    }
}
