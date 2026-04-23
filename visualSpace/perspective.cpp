struct perspective {
    public:
        float camYaw = 0; 
        float camPitch = 0;
        float camRadius = 3.0f;

        perspective(float x, float y, float z){
            camYaw = x;
            camPitch = y;
            camRadius = z;
        }
};
