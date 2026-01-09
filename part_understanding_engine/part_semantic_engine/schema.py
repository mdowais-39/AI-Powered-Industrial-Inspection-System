from pydantic import BaseModel, Field
from typing import List, Optional, Literal


class Measurement(BaseModel):
    name: str = Field(
        ..., description="Name of the measurement (e.g. length, diameter)"
    )
    value: Optional[float] = Field(
        None, description="Numeric value if known, otherwise null"
    )
    unit: Optional[str] = Field(
        None, description="Unit of measurement (e.g. mm, cm)"
    )
    source: Literal["user", "llm", "unknown"] = Field(
        ..., description="Origin of the measurement value"
    )


class Component(BaseModel):
    name: str = Field(
        ..., description="Generic component name"
    )
    description: str = Field(
        ..., description="Vision-only description of the component"
    )
    approximate_location: Optional[str] = Field(
        None, description="Approximate visual location (top, center, left, etc.)"
    )
    measurements: List[Measurement] = Field(
        default_factory=list,
        description="Measurements associated with this component"
    )


class PartTemplate(BaseModel):
    part_name: Optional[str] = Field(
        None,
        description="Generic part name if known; must not include manufacturer or model"
    )
    description: str = Field(
        ..., description="Overall vision-only description of the part"
    )
    components: List[Component] = Field(
        default_factory=list,
        description="List of visible components"
    )
    confidence: float = Field(
        ...,
        ge=0.0,
        le=1.0,
        description="Confidence score for the visual understanding"
    )
