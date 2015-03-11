
public class IntersenseDump {
    static {
        // Load native library
        System.loadLibrary("vrpn_tracker");
    }
    private native void addRotListener(VrpnTracker.RotListener listener);

    public static void main(String[] args) {
        IntersenseDump jniTest = new IntersenseDump();
        jniTest.addRotListener(new VrpnTracker.RotListener() {
            public void onRotationalChange(double x, double y, double z, double r) {
                System.out.println("Hello Callbacks!");
            }
        });

        System.out.println("Send callback to C++!");
    }
}

