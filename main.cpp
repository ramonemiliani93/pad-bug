#include "itkPipeline.h"
#include "itkOutputImage.h"
#include "itkConstantPadImageFilter.h"
#include "itkImage.h"

int main(int argc, char * argv[]) {
    itk::wasm::Pipeline pipeline("pad-bug", "Pad Bug", argc, argv);

    using ImageType = itk::Image<unsigned char, 3>;

    using IOOutputImageType = itk::wasm::OutputImage<ImageType>;
    IOOutputImageType ioOutputImage;
    pipeline.add_option("output-image", ioOutputImage, "Output image")->required()->type_name("OUTPUT_IMAGE");

    ITK_WASM_PARSE(pipeline);

    auto image = ImageType::New();

    ImageType::IndexType start;
    start[0] = 0;
    start[1] = 0;
    start[2] = 0;

    ImageType::SizeType size;
    size[0] = 3;
    size[1] = 3;
    size[2] = 3;

    ImageType::RegionType region;
    region.SetSize(size);
    region.SetIndex(start);

    image->SetRegions(region);
    image->Allocate();

    typename ImageType::SizeType lowerBoundPadding;
    typename ImageType::SizeType upperBoundPadding;

    lowerBoundPadding.Fill(3);
    upperBoundPadding.Fill(3);

    using FilterType = itk::ConstantPadImageFilter<ImageType, ImageType>;
    auto filter = FilterType::New();

    filter->SetInput(image);
    filter->SetPadLowerBound(lowerBoundPadding);
    filter->SetPadUpperBound(upperBoundPadding);
    filter->Update();

    auto padded = filter->GetOutput();
    ioOutputImage.Set(padded);

    std::cout << "Hello" << std::endl;

    return EXIT_SUCCESS;
}
