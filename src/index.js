import * as itkWasm from 'itk-wasm';

const outputTextArea = document.querySelector("textarea");
outputTextArea.textContent = "Loading...";

const wasmURL = new URL('pad_bug', document.location)
const args = ["--memory-io", "0"];
const inputs = []
const outputs =  [{ type: itkWasm.InterfaceTypes.Image }];

itkWasm.runPipeline(wasmURL, args, outputs, inputs).then(
({ stdout, webWorker, outputs }) => {
    webWorker.terminate();
    console.log(stdout);
    console.log(outputs[0].data.origin);
    outputTextArea.textContent = "Done!";
})
