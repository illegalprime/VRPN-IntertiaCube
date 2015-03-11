public class VrpnTracker {
    public interface RotListener {
        void onRotationalChange(double x, double y, double z, double theta);
    }
    public interface PosListener {
        void onPositionalChange(double x, double y, double z);
    }
}
