const path = require("path");
const CopyPlugin = require("copy-webpack-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = () => ({
    mode: "development",
    entry: { index: path.resolve(__dirname, "src/index.js") },
    output: {
        path: path.resolve(__dirname, "dist"),
        filename: "[name].js",
        clean: true,
    },
    devtool: "inline-source-map",
    devServer: {
        static: {
            directory: path.join(__dirname, "dist"),
        },
        port: 8080,
        open: true,
        hot: true,
        compress: true,
        watchFiles: ["src/**/*", "emscripten-build/**/*"],
        headers: {
            "Cross-Origin-Embedder-Policy": "require-corp",
            "Cross-Origin-Opener-Policy": "same-origin",
        },
    },
    plugins: [
        new HtmlWebpackPlugin({
            filename: "index.html",
            template: "src/index.html",
        }),
        new CopyPlugin({
            patterns: [
                {
                    from: "emscripten-build/*",
                    to: "[name][ext]",
                },
            ],
        }),
    ],
});
