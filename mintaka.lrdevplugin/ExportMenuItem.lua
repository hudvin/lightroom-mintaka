local LrTasks = import 'LrTasks'
local LrDialogs = import 'LrDialogs'
local lrApplication = import 'LrApplication'
local LrShell = import 'LrShell'
local LrExportSession = import 'LrExportSession'


local function getSelection ()
	 local catalog = lrApplication.activeCatalog()
	 if catalog:getTargetPhoto () then
	      return catalog:getTargetPhotos ()
     else
	      return {}
          end
     end

local function performExport()
	
	LrTasks.startAsyncTask(function()
	  local catalog = lrApplication.activeCatalog()
	  local photos = getSelection()
	  
	  if next(photos) == nil then
	     LrDialogs.message("Please, select some photos!")
	     return {}
      end
	  
	  local exportSettings = {
                        LR_format = "JPEG",
                        LR_export_colorSpace = "sRGB",
                        LR_export_useSubfolder = false,
                        LR_jpeg_quality = 100,
                        LR_size_resolution = 72,
                        LR_size_resolutionUnits = "inch",
                        LR_outputSharpeningOn = false,
                        LR_export_destinationType = "specificFolder",
                        LR_export_destinationPathPrefix = 'c:/dev/images/',
                        LR_collisionHandling = "skip",
						LR_extensionCase = "lowercase",
						LR_jpeg_useLimitSize = false,  
                        LR_size_doConstrain = true,  
                        LR_size_maxHeight = 300,  
                        LR_size_maxWidth = 300,  
                        LR_size_units = "pixels",  
                        LR_size_resizeType = "wh",  
						LR_tokens = {{image_originalName_number_suffix}},
      }

      local params =  {
                        photosToExport = photos,
                        exportSettings = exportSettings
                       }
      local ex = LrExportSession(params)
      
	    ex:doExportOnCurrentTask()

      for i, rendition in ex:renditions() do
        local status, other = rendition:waitForRender()
      end
	  
	   
	end
	)
end

performExport()


