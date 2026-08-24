import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

// https://vitejs.dev/config/
export default defineConfig({
  base: "/ParaLink-Eye-Gaze-Tracking-System/",
  plugins: [react()],
  optimizeDeps: {
    exclude: ["lucide-react"],
  },
});
